from copy import copy
from .matrix import Matrix


def iterate(matrix_a, matrix_b, matrix_x):
    new_matrix_x = Matrix(matrix_x.rows, matrix_x.columns).init(0)
    for i in range(matrix_a.rows):
        row = copy(matrix_a[i])
        x_main = - row[i]
        new_matrix_x[i][0] = matrix_b[i][0] / (-x_main)
        row[i] = 0
        for j in range(matrix_a.columns):
            new_matrix_x[i][0] += row[j] / x_main * matrix_x[j][0]
    return new_matrix_x


def calculate_difference(matrix_prev, matrix_next):
    if (matrix_prev.rows == matrix_next.rows and matrix_prev.columns == matrix_next.columns):
        return _calculate_diff_evkl(matrix_prev, matrix_next)
    else:
        raise Exception("ERROR: compared matrixes have different dimensions")


def _calculate_diff_evkl(m1, m2):
    result = 0.0
    for i in range(m1.rows):
        for j in range(m1.columns):
            result += (m1[i][j] - m2[i][j]) ** 2
    return result ** 0.5

