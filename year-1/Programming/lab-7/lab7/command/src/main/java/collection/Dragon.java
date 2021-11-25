package collection;

import java.io.Serializable;
import java.time.Instant;
import java.time.ZonedDateTime;
import java.time.format.DateTimeFormatter;

/**
 * Класс объектов(значений) коллекции.
 */
public class Dragon implements Serializable {

    private final static long serialVersionUID = 19371893193713L;

    private static int uniqueId = 1;

    /**
     * Уникальный идентификатор коллекции. Поле не может быть null, Значение поля должно быть больше 0, Значение этого поля должно быть уникальным, значение этого поля генерируется автоматически.
     */
    private final Integer id;
    /**
     * Координаты объекта класса. Поле не может быть null.
     */
    private final Coordinates coordinates;
    /**
     * Время создания объекта класса. Поле не может быть null, Значение генерируется автоматически.
     */
    private final ZonedDateTime creationDate;
    /**
     * Uмя объекта класса. Поле не может быть null, Строка не может быть пустой.
     */
    private String name;
    /**
     * Возраст объекта класса. Значение поля должно быть больше 0, Поле может быть null.
     */
    private Long age;

    /**
     * Цвет объекта класса. Поле не может быть null.
     */
    private Color color;

    /**
     * Тип объекта класса. Поле не может быть null.
     */
    private DragonType type;

    /**
     * Характер объекта класса. Поле не может быть null.
     */
    private DragonCharacter character;

    /**
     * Уровень пещеры объекта класса. Поле не может быть null.
     */

    private DragonCave cave;

    private String user_login;

    /**
     * Конструктор объекта класса.
     *
     * @param name            имя объекта класса.
     * @param coordinates     координаты объекта класса.
     * @param color           цвет объекта класса.
     * @param dragonType      тип объекта класса.
     * @param dragonCharacter характер объекта класса.
     * @param dragonCave      уровень пещеры объекта класса.
     * @param zonedDateTime   время создания объекта класса.
     */
    public Dragon(String name, Coordinates coordinates, Color color, DragonType dragonType, DragonCharacter dragonCharacter, DragonCave dragonCave, ZonedDateTime zonedDateTime) {
        this.id = uniqueId++;
        this.name = name;
        this.coordinates = coordinates;
        this.color = color;
        this.type = dragonType;
        this.character = dragonCharacter;
        this.cave = dragonCave;
        this.creationDate = zonedDateTime;
    }

    /**
     * Конструктор объекта класса.
     *
     * @param id              уникальный идентификатор объекта коллекции.
     * @param name            имя объекта класса.
     * @param coordinates     координаты объекта класса.
     * @param color           цвет объекта класса.
     * @param age             возраст объекта класса.
     * @param dragonType      тип объекта класса.
     * @param dragonCharacter характер объекта класса.
     * @param dragonCave      уровень пещеры объекта класса.
     * @param zonedDateTime   время создания объекта класса.
     */
    public Dragon(Integer id, String name, Coordinates coordinates, Color color, Long age, DragonType dragonType, DragonCharacter dragonCharacter, DragonCave dragonCave, ZonedDateTime zonedDateTime) {
        this.id = id;
        this.name = name;
        this.coordinates = coordinates;
        this.color = color;
        this.type = dragonType;
        this.character = dragonCharacter;
        this.cave = dragonCave;
        this.creationDate = zonedDateTime;
        this.age = age;
    }

    public static Dragon createDragon(Integer id, String name, Double x, Integer y, Long age, Color color, DragonType type, DragonCharacter dc, Double depth, ZonedDateTime creationDate, String owner) {

        Coordinates coordinates = new Coordinates(x);
        int intY;
        if (y != null) {
            intY = y;
            coordinates.setY(intY);
        }

        DragonCave cave = new DragonCave();
        if (depth != null) cave.setDepth(depth);

        Dragon dragon = new Dragon(id, name, coordinates, color, age, type, dc, cave, creationDate);
        dragon.setOwner(owner);
        return dragon;

    }

    @Deprecated
    public static Dragon createDragonWithoutOwner(String name, Double x, Integer y, Long age, Color color, DragonType type, DragonCharacter dc, Double depth, ZonedDateTime creationDate) {

        if ((name != null && !name.isEmpty()) && (x != null && x > -648) && (y == null || y <= 803) && (age == null || age > 0)
                && (color != null) && (type != null) && (dc != null)) {

            Coordinates coordinates = new Coordinates(x);
            int intY;
            if (y != null) {
                intY = y;
                coordinates.setY(intY);
            }

            DragonCave cave = new DragonCave();
            if (depth != null) cave.setDepth(depth);

            if (creationDate == null) {
                String i = Instant.now().toString();
                creationDate = ZonedDateTime.parse(i);
            }

            Dragon dragon = new Dragon(name, coordinates, color, type, dc, cave, creationDate);

            if (age != null) {
                dragon.setAge(age);
            }
            return dragon;

        } else return null;
    }

    /**
     * Метод, возвращающий идентификатор объекта класса.
     *
     * @return id - идентификатор объекта класса.
     */
    public Integer getId() {
        return id;
    }

    /**
     * Метод, возвращающий имя объекта класса.
     *
     * @return name - имя объекта класса.
     */
    public String getName() {
        return name;
    }

    /**
     * Метод, присваивающий имя объекта класса.
     *
     * @param name имя объекта класса.
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Метод, возвращающий координаты объекта класса.
     *
     * @return Coordinates - координаты объекта класса.
     */
    public Coordinates getCoordinates() {
        return coordinates;
    }

    /**
     * Метод, возвращающий время создания объекта класса.
     *
     * @return ZonedDateTime - время создания объекта класса.
     */
    public ZonedDateTime getCreationDate() {
        return creationDate;
    }

    /**
     * Метод, возвращающий отформатированное время создания объекта класса.
     *
     * @return String - отформатированное время создания объекта класса.
     */
    public String getFormattedCreationDate() {
        String pattern = "yyyy-MM-dd HH:mm:ss.SSS";
        DateTimeFormatter europeanDateFormatter = DateTimeFormatter.ofPattern(pattern);
        return creationDate.plusHours(3).format(europeanDateFormatter);
    }

    /**
     * Метод, возвращающий возраст объекта класса.
     *
     * @return Long - возраст объекта класса.
     */
    public Long getAge() {
        return age;
    }

    /**
     * Метод, присваивающий возраст объекта класса.
     *
     * @param age возраст объекта класса.
     */
    public void setAge(Long age) {
        this.age = age;
    }

    /**
     * Метод, возвращающий цвет объекта класса.
     *
     * @return Color - цвет объекта класса.
     */
    public Color getColor() {
        return color;
    }

    /**
     * Метод, присваивающий цвет объекта класса.
     *
     * @param color цвет объекта класса.
     */
    public void setColor(Color color) {
        this.color = color;
    }

    /**
     * Метод, возвращающий тип объекта класса.
     *
     * @return Type - тип объекта класса.
     */
    public DragonType getType() {
        return type;
    }

    /**
     * Метод, присваивающий тип объекта класса.
     *
     * @param type тип объекта класса.
     */
    public void setType(DragonType type) {
        this.type = type;
    }

    /**
     * Метод, возвращающий характер объекта класса.
     *
     * @return DragonCharacter - характер объекта класса.
     */
    public DragonCharacter getCharacter() {
        return character;
    }

    /**
     * Метод, присваивающий характер объекта класса.
     *
     * @param character характер объекта класса.
     */
    public void setCharacter(DragonCharacter character) {
        this.character = character;
    }

    /**
     * Метод, возвращающий уровень пещеры объекта класса.
     *
     * @return DragonCave - уровень пещеры объекта класса.
     */
    public DragonCave getCave() {
        return cave;
    }

    /**
     * Метод, присваивающий пещеру объекта класса.
     *
     * @param cave пещера объекта класса.
     */
    public void setCave(DragonCave cave) {
        this.cave = cave;
    }

    /**
     * Метод, присваивающий координату x объекта класса.
     *
     * @param x координата объекта класса.
     */
    public void setCoordinateX(Double x) {
        this.getCoordinates().setX(x);
    }

    /**
     * Метод, присваивающий координату y объекта класса.
     *
     * @param y координата y объекта класса.
     */
    public void setCoordinateY(int y) {
        this.getCoordinates().setY(y);
    }

    /**
     * Метод, присваивающий глубину пещеры объекта класса.
     *
     * @param depth глубина пещеры объекта класса.
     */
    public void setCaveDepth(Double depth) {
        this.cave.setDepth(depth);
    }

    public String getOwner() {
        return user_login;
    }

    public void setOwner(String owner) {
        this.user_login = owner;
    }

    /**
     * Метод, возвращающий отформатированный вывод полей объекта класса.
     *
     * @return String - поля объекта класса.
     */
    public String toString() {
        return "Dragon id = " + this.getId() + ":\n\tname: " + this.getName() + "\n\t" + this.getCoordinates().toString() + "\n\tage: " + this.getAge() + "\n\tcolor: "
                + this.getColor().toString() + "\n\ttype: " + this.getType().toString() + "\n\tcharacter : " + this.getCharacter() +
                "\n\tcave_depth: " + this.getCave().toString() + "\n\tcreation_date: " + this.getFormattedCreationDate() + "\n\towner: " + this.getOwner();
    }
}