import java.util.ArrayList;

public class ArgPassing {
    
    public void doSomething(int i) {
        i += 100;
    }

    public void doSomething(Integer i) {
        i += 100;
    }
    
    public void doString(String s) {
        s += " World";
    }

    public void doArrList(ArrayList<String> al) {
        al.add("Hello");
        al.add("World");
        al = new ArrayList<>();
        al.add("Hello Again");
    }

    public static void main(String[] args) {
        ArgPassing ap = new ArgPassing();   
        int a = 100;
        Integer b = new Integer(100);
        ap.doSomething(a);
        ap.doSomething(b);

        String s = "Hello";
        ap.doString(s);

        ArrayList<String> al = new ArrayList<String>();
        ap.doArrList(al);

    }
}
