public class TypeCast {

    public static void doWrapperClass() {
        short s = 123;
        int i = 1111111;
        long l = 123456789999990L;

        Short s1 = new Short(s);
        Integer i1 = new Integer(i);
        Long l1 = new Long(l);

        Integer i2 = Integer.valueOf(s1.intValue());
        Integer i3 = Integer.valueOf(i1.intValue());
    }

    public static void doTypeCast() {
        short s = 123;
        int i = 1111111;
        long l = 1234567890;

        //l = i; // allowed
        //s = i; // not allowed
        //i = l; // not allowed

        float f = 1.234f;
        double d = 1.23456789;

        //d = f; // allowed
        //f = d; // not allowed
        //f = (float) d; // allowed

        System.out.println(d);
        System.out.println(f);
    }

    public static void main(String[] args) {
        //doTypeCast();
        doWrapperClass();
    }
}
