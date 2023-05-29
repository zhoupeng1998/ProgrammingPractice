import javax.swing.JButton;
import javax.swing.JFrame;

import java.awt.event.ActionListener;
import java.awt.Frame;
import java.awt.event.ActionEvent;

class MyFrame extends JFrame {
    public MyFrame() {
        setTitle("MyFrame");
        setSize(300, 200);
        setLocationRelativeTo(null);
        setLayout(null);

        MyButton button = new MyButton("Click me!");
        add(button);

        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setVisible(true);
    }
}

class MyButton extends JButton {
    public MyButton(String label) {
        super(label);
        setBounds(10, 10, 100, 50);
        addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                System.out.println("Button pressed!");
            }
        });
    }
}

public class GUI {
    public static void main(String[] args) {
        /*
        JFrame frame = new MyFrame();
        frame.setSize(300, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JButton button = new MyButton("Click me!");
        button.setBounds(10, 10, 100, 50);
        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                System.out.println("Button pressed!");
            }
        });
        frame.add(button);

        frame.setLayout(null);
        frame.setVisible(true);
        */

        Frame frame = new MyFrame();
    }
}