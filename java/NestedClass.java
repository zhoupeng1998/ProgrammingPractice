public class NestedClass {

    private ClassA aInstance;
    private ClassB bInstance;
    private int info = 567;

    private class ClassA {
        private int a_info = 123;

        private void foo() {
            System.out.print("foo() in ClassA ");
            System.out.println("info = " + info);
        }

        private void bar() {
            System.out.println(bInstance.b_info);
        }
    }

    private class ClassB {
        private int b_info = 456;
    }

    public NestedClass() {
        aInstance = new ClassA();
        bInstance = new ClassB();
    }

    public void testA() {
        aInstance.foo();
        aInstance.bar();
    }

    public static void main(String[] args) {
        NestedClass nc = new NestedClass();
        nc.testA();
    }
}
