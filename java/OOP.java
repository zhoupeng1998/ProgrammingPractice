class Animal {
    private int age;

    public Animal(int age) {
        this.age = age;
    }
    
    public void eat() {
        System.out.println("Animal is eating");   
    }

    private void makeSound() {
        System.out.println("Animal is making sound");   
    }
}

class Dog extends Animal {

    public Dog(int age) {
        super(age);
    }
    
    public String eat(String food) {
        System.out.println("Dog is eating " + food);   
        return "Poop";
    }

    public void makeSound() {
        System.out.println("Dog is making sound: woof!");   
    }

    public void bark() {
        System.out.println("Woof! Woof!");
    }
}

public class OOP {
    public static void main(String[] args) {
        Animal a = new Animal(5);
        Animal b = new Dog(10);
        Dog c = new Dog(15);

        //a.eat();
        //a.makeSound();
        //a.bark();

        //b.eat();
        //b.makeSound();
        //b.bark();

        //c.eat();
        //c.makeSound();
        //c.bark();

        //((Dog) b).bark();
        //((Dog) a).bark();
    }
}
