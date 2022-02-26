package ru.nkulakov.commands;

import ru.nkulakov.commands.abstr.Command;
import ru.nkulakov.commands.abstr.InvocationStatus;
import ru.nkulakov.database.UserData;
import ru.nkulakov.exceptions.CannotExecuteCommandException;

import java.io.PrintStream;
import java.util.HashMap;
import java.util.concurrent.locks.Lock;

/**
 * Класс команды, которая выводит описания всех команд, реализованных в программе.
 */
public class HelpCommand extends Command {
    /**
     * Коллекция, содержащая объекты всех доступных в программе команд без дополнительных аргументов.
     */
    private final HashMap<String, Command> commands;

    /**
     * Конструктор класса.
     *
     * @param commands Коллекция, содержащая объекты всех доступных в программе команд с дополнительными аргументами.(либо клиентские, либо сервера)
     */
    public HelpCommand(HashMap<String, Command> commands) {
        super("help");
        this.commands = commands;
    }

    /**
     * Метод, выводящий справку по всем доступным командам.
     *
     * @param invocationEnum режим, с которым должна быть исполнена данная команда.
     * @param printStream    поток вывода.
     * @param arguments      аргументы команды.
     */
    public void execute(String[] arguments, InvocationStatus invocationEnum, PrintStream printStream, UserData userData, Lock locker) throws CannotExecuteCommandException {
        if (invocationEnum.equals(InvocationStatus.CLIENT)) {
            if (arguments.length > 0) {
                throw new CannotExecuteCommandException("У данной команды нет аргументов.");
            } else {
                commands.forEach((key, value) -> printStream.println(key + ": " + value.getDescription() + "\n"));
            }
        } else if (invocationEnum.equals(InvocationStatus.SERVER)) {
            commands.forEach((key, value) -> printStream.println(key + ": " + value.getDescription() + "\n"));
        }
    }

    /**
     * Метод, возвращающий описание команды.
     *
     * @return Описание данной команды.
     * @see HelpCommand
     */
    @Override
    public String getDescription() {
        return "sout the commands info";
    }
}