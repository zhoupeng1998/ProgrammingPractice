import java.awt.image.BufferedImage;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;


public class MyCompression {

    private static final int ITERATIONS = 30;

    private static final int WIDTH = 352;
    private static final int HEIGHT = 288;

    private int numVectors = 16;

    private int vectorWidth = 1;
    private int vectorHeight = 2;

    private BufferedImage inputImage;
    private BufferedImage outputImage;

    private List<Integer> vectorIndices;
    private List<List<List<Integer>>> centroidVectors;

    // compress
    private ArrayList<ArrayList<Integer>> clusters;
    private List<List<AggRGB>> newCentroid;

    // display
    private JFrame frame;
    private GridBagLayout layout;
    private JLabel labelInputText;
    private JLabel labelOutputText;
    private JLabel labelInputImage;
    private JLabel labelOutputImage;

    public MyCompression() {
        vectorIndices = new ArrayList<>();
        centroidVectors = new ArrayList<>();
    }

    public MyCompression(int vectorSize, int numVectors) {
        if (vectorSize == 2) {
            this.vectorWidth = 2;
            this.vectorHeight = 1;
        } else {
            // check if vectorSize is a perfect square
            int sqrt = (int) Math.sqrt(vectorSize);
            if (sqrt * sqrt != vectorSize) {
                System.err.println("Error: vectorSize must be a perfect square or 2.");
                System.exit(1);
            }
            this.vectorWidth = (int) Math.sqrt(vectorSize);
            this.vectorHeight = (int) Math.sqrt(vectorSize);
        }
        // check if numVectors is power of 2
        if ((numVectors & (numVectors - 1)) != 0) {
            System.err.println("Error: numVectors must be a power of 2.");
            System.exit(1);
        }
        this.numVectors = numVectors;
        System.out.println("numvector: " + numVectors);
        vectorIndices = new ArrayList<>();
        centroidVectors = new ArrayList<>();
    }

    // loadimage
    public void loadImage(String inputImagePath) {
        // Load the input image
        try {
            inputImage = ImageIO.read(new File(inputImagePath));

            JLabel label = new JLabel(new ImageIcon(inputImage));
            JPanel panel = new JPanel(new BorderLayout());
            panel.add(label, BorderLayout.CENTER);
            JFrame frame = new JFrame();

            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.getContentPane().add(panel);
            frame.pack();
            frame.setVisible(true);
        } catch (IOException ex) {
            System.err.println("Error loading the image.");
            ex.printStackTrace();
        }
    }

    public void readGrayscaleImage(File file) throws IOException {
        DataInputStream in = new DataInputStream(new FileInputStream(file));
        inputImage = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_BYTE_GRAY);
        outputImage = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_BYTE_GRAY);
        byte[] data = new byte[WIDTH * HEIGHT];
        int bytesRead = 0;
        int count = 0;
        while (bytesRead < data.length) {
            int result = in.read(data, bytesRead, data.length - bytesRead);
            System.out.println("result: " + result);
            if (result == -1) {
                break;
            }
            bytesRead += result;
            System.out.println(count++);
        }
        in.close();
        inputImage.getRaster().setDataElements(0, 0, WIDTH, HEIGHT, data);
        // print inputImage rgb
        /*
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                int rgb = inputImage.getRGB(x, y);
                int r = (rgb >> 16) & 0xFF;
                int g = (rgb >> 8) & 0xFF;
                int b = (rgb) & 0xFF;
                System.out.println("r: " + r + " g: " + g + " b: " + b);
            }
        }
        */
        // print everyting in data
        /*
        for (int i = 0; i < data.length; i++) {
            System.out.println(data[i]);
        }
        */
    }

    public void readRGBImage2(File file) throws IOException {
        DataInputStream in = new DataInputStream(new FileInputStream(file));
        inputImage = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_RGB);
        byte[] buffer = new byte[3];
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                in.readFully(buffer);
                int r = buffer[0] & 0xFF;
                int g = buffer[1] & 0xFF;
                int b = buffer[2] & 0xFF;
                int rgb = (r << 16) | (g << 8) | b;
                inputImage.setRGB(x, y, rgb);;
            }
        }
        in.close();
    }

    public void readRGBImage(File file) throws IOException {
        DataInputStream in = new DataInputStream(new FileInputStream(file));
        inputImage = new BufferedImage(WIDTH, HEIGHT, BufferedImage.TYPE_INT_RGB);
        byte[] data = new byte[WIDTH * HEIGHT * 3]; // Allocate memory for the RGB data
        int bytesRead = 0;
        while (bytesRead < data.length) {
            int count = in.read(data, bytesRead, data.length - bytesRead);
            //System.out.println("count: " + count);
            if (count == -1) {
                break;
            }
            bytesRead += count;
        }
        in.close();
        // Set the RGB data in the BufferedImage
        int[] rgb = new int[3];
        int k = 0;
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                for (int i = 0; i < 3; i++) {
                    rgb[i] = data[k++] & 0xff; // Extract the i-th channel
                }
                int pixel = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2]; // Combine the channels into an RGB pixel
                inputImage.setRGB(x, y, pixel);
            }
        }
        //System.out.println(k);
        in.close();
    }
    
    // display image in a window
    public void displayImage() {

        frame = new JFrame();
        layout = new GridBagLayout();
        frame.getContentPane().setLayout(layout);

        labelInputText = new JLabel("Original image (Left)");
        labelOutputText = new JLabel("Compressed image (Right)");
        labelInputText.setHorizontalAlignment(SwingConstants.CENTER);
        labelOutputText.setHorizontalAlignment(SwingConstants.CENTER);

        labelInputImage = new JLabel(new ImageIcon(inputImage));
        labelOutputImage = new JLabel(new ImageIcon(outputImage));

        GridBagConstraints c = new GridBagConstraints();
        c.fill = GridBagConstraints.HORIZONTAL;
        c.anchor = GridBagConstraints.CENTER;
        c.weightx = 0.5;
        c.gridx = 0;
        c.gridy = 0;
        frame.getContentPane().add(labelInputText, c);

        c.fill = GridBagConstraints.HORIZONTAL;
        c.anchor = GridBagConstraints.CENTER;
        c.weightx = 0.5;
        c.gridx = 1;
        c.gridy = 0;
        frame.getContentPane().add(labelOutputText, c);

        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 0;
        c.gridy = 1;
        frame.getContentPane().add(labelInputImage, c);

        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 1;
        c.gridy = 1;
        frame.getContentPane().add(labelOutputImage, c);

        frame.pack();
        frame.setVisible(true);
    }

    public void displayNewImage() {
        labelOutputImage.setIcon(new ImageIcon(outputImage));
    }
    
    // 2-pixel vector index to image pixel position, returns (x,y) coordinate
    public int[] indexToPosition(int index) {
        int[] position = new int[2];
        position[0] = index % WIDTH;
        position[1] = index / WIDTH;
        return position;
    }

    // image pixel position to 2-pixel vector index
    public int positionToIndex(int x, int y) {
        return y * WIDTH + x;
    }

    public void initVectors0() {
        // add 2-pixel vector indexes of image to list
        for (int y = 0; y < HEIGHT; y += vectorHeight) {
            for (int x = 0; x < WIDTH; x += vectorWidth) {
                vectorIndices.add(y * WIDTH + x);
            }
        }
        // divide image into sqrt(numVectors) areas, take the center pixel of each area as centroid
        int areaWidth = WIDTH / (int) Math.sqrt(numVectors);
        int areaHeight = HEIGHT / (int) Math.sqrt(numVectors);
        //System.out.println("areaWidth: " + areaWidth + ", areaHeight: " + areaHeight);
        for (int y = 0; y < HEIGHT; y += areaHeight) {
            for (int x = 0; x < WIDTH; x += areaWidth) {
                int ypos = y + areaHeight / 2;
                int xpos = x + areaWidth / 2;
                if (ypos >= HEIGHT || xpos >= WIDTH) {
                    continue;
                }
                List<List<Integer>> initVector = new ArrayList<List<Integer>>();
                for (int h = 0; h < vectorHeight; h++) {
                    List<Integer> row = new ArrayList<Integer>();
                    for (int w = 0; w < vectorWidth; w++) {
                        //System.out.println("xpos + w: " + (xpos + w) + ", ypos + h: " + (ypos + h));
                        row.add(inputImage.getRGB(xpos + w, ypos + h));
                    }
                    initVector.add(row);
                }
                centroidVectors.add(initVector);
            }
        }
        //System.out.println("centrodVectors size: " + centroidVectors.size());
    }

    public void initVectors() {
        // add 2-pixel vector indexes of image to list
        for (int y = 0; y < HEIGHT; y += vectorHeight) {
            for (int x = 0; x < WIDTH; x += vectorWidth) {
                vectorIndices.add(y * WIDTH + x);
            }
        }
        for (int i = 0; i < numVectors; i++) {
            int index = (int) (Math.random() * vectorIndices.size());
            List<List<Integer>> initVector = getVector(vectorIndices.get(index));
            centroidVectors.add(initVector);
        }
    }

    // get vector from image at index
    public List<List<Integer>> getVector(int index) {
        List<List<Integer>> vector = new ArrayList<List<Integer>>();
        int[] position = indexToPosition(index);
        for (int y = 0; y < vectorHeight; y++) {
            List<Integer> row = new ArrayList<Integer>();
            for (int x = 0; x < vectorWidth; x++) {
                int xpos = position[0] + x;
                int ypos = position[1] + y;
                int rgb = 0;
                if (xpos < WIDTH && ypos < HEIGHT) {
                    rgb = inputImage.getRGB(xpos, ypos);
                }
                row.add(rgb);
            }
            vector.add(row);
        }
        return vector;
    }

    // get distance of two rgb pixels
    public double getPixelDistance(int rgb1, int rgb2) {
        int r1 = (rgb1 >> 16) & 0xFF;
        int g1 = (rgb1 >> 8) & 0xFF;
        int b1 = rgb1 & 0xFF;
        int r2 = (rgb2 >> 16) & 0xFF;
        int g2 = (rgb2 >> 8) & 0xFF;
        int b2 = rgb2 & 0xFF;
        return Math.sqrt(Math.pow(r1 - r2, 2) + Math.pow(g1 - g2, 2) + Math.pow(b1 - b2, 2));
    }

    // get distance of two n-pixel vectors from vectorIndices
    public double getVectorDistance(int index, List<List<Integer>> vector) {
        //System.out.println("index: " + index);
        double distance = 0;
        for (int y = 0; y < vectorHeight; y++) {
            for (int x = 0; x < vectorWidth; x++) {
                //System.out.println("x: " + x + ", y: " + y);
                int xpos = indexToPosition(index)[0] + x;
                int ypos = indexToPosition(index)[1] + y;
                int rgb1 = 0;
                if (xpos < WIDTH && ypos < HEIGHT) {
                    rgb1 = inputImage.getRGB(xpos, ypos);
                }
                int rgb2 = vector.get(y).get(x);
                distance += getPixelDistance(rgb1, rgb2);
            }
        }
        return distance;
    }

    public void runIteration(int clusterId) {
        //System.out.println("Running iteration " + clusterId);
        //System.out.println("vectors in cluster: " + clusters.get(clusterId).size());
        for (int y = 0; y < vectorHeight; y++) {
            for (int x = 0; x < vectorWidth; x++) {
                newCentroid.get(y).get(x).clear();
            }
        }
        for (int k = 0; k < clusters.get(clusterId).size(); k++) {
            int index = clusters.get(clusterId).get(k);
            for (int y = 0; y < vectorHeight; y++) {
                for (int x = 0; x < vectorWidth; x++) {
                    int xpos = indexToPosition(index)[0] + x;
                    int ypos = indexToPosition(index)[1] + y;
                    int rgb = 0;
                    if (xpos < WIDTH && ypos < HEIGHT) {
                        rgb = inputImage.getRGB(xpos, ypos);
                    }
                    newCentroid.get(y).get(x).addPixel(rgb);
                }
            }
        }
        for (int y = 0; y < vectorHeight; y++) {
            for (int x = 0; x < vectorWidth; x++) {
                centroidVectors.get(clusterId).get(y).set(x, newCentroid.get(y).get(x).getRGB());
            }
        }
    }

    public void compressImage() {
        // clusters
        clusters = new ArrayList<ArrayList<Integer>>();
        for (int i = 0; i < numVectors; i++) {
            clusters.add(new ArrayList<Integer>());
        }
        // initialize centroid list object
        newCentroid = new ArrayList<List<AggRGB>>();
        for (int y = 0; y < vectorHeight; y++) {
            List<AggRGB> row = new ArrayList<AggRGB>();
            for (int x = 0; x < vectorWidth; x++) {
                row.add(new AggRGB());
            }
            newCentroid.add(row);
        }
        // iterate for 50 times
        for (int i = 0; i < ITERATIONS; i++) {
            // clear clusters
            for (int j = 0; j < clusters.size(); j++) {
                clusters.get(j).clear();
            }
            // assign vectors to clusters
            // for each vector
            for (int j = 0; j < vectorIndices.size(); j++) {
                int index = vectorIndices.get(j);
                double minDistance = Double.MAX_VALUE;
                int minIndex = -1;
                // find closest centroid
                for (int k = 0; k < centroidVectors.size(); k++) {
                    double distance = getVectorDistance(index, centroidVectors.get(k));
                    if (distance < minDistance) {
                        minDistance = distance;
                        minIndex = k;
                    }
                }
                clusters.get(minIndex).add(index);
            }
            // update centroids (single threaded)
            for (int j = 0; j < clusters.size(); j++) {
                runIteration(j);
                
            }
            int progress = (int)((float) i / 30 * 100);
            System.out.println("Clustering " + progress + "%, please wait...");

            /*
            // print each cluster size
            for (int k = 0; k < clusters.size(); k++) {
                System.out.print(clusters.get(k).size() + " ");
            }
            System.out.println();
            */
            // update centroids (multithreaded)
            /*
            Thread[] threads = new Thread[clusters.size()];
            for (int j = 0; j < clusters.size(); j++) {
                ClusterComputation computation = new ClusterComputation(j, this);
                threads[j] = new Thread(computation);
                threads[j].start();
                //runIteration(j);
            }
            for (int j = 0; j < clusters.size(); j++) {
                try {
                    threads[j].join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            */
        }
        // assign result to outputImage
        for (int i = 0; i < vectorIndices.size(); i++) {
            int index = vectorIndices.get(i);
            double minDistance = Double.MAX_VALUE;
            int minIndex = -1;
            for (int j = 0; j < centroidVectors.size(); j++) {
                double distance = getVectorDistance(index, centroidVectors.get(j));
                if (distance < minDistance) {
                    minDistance = distance;
                    minIndex = j;
                }
            }
            for (int y = 0; y < vectorHeight; y++) {
                for (int x = 0; x < vectorWidth; x++) {
                    int rgb = centroidVectors.get(minIndex).get(y).get(x);
                    int xpos = indexToPosition(index)[0] + x;
                    int ypos = indexToPosition(index)[1] + y;
                    if (xpos < WIDTH && ypos < HEIGHT) {
                        outputImage.setRGB(xpos, ypos, rgb);
                    }
                    //outputImage.setRGB(indexToPosition(index)[0] + x, indexToPosition(index)[1] + y, rgb);
                }
            }
        }
        System.out.println("Done!");
        // print elements in centroidVectors
        /*
        for (int i = 0; i < centroidVectors.size(); i++) {
            System.out.println("Centroid " + i);
            for (int y = 0; y < vectorHeight; y++) {
                for (int x = 0; x < vectorWidth; x++) {
                    System.out.print(centroidVectors.get(i).get(y).get(x) + " ");
                }
                System.out.println();
            }
        }
        */
    }

    public static void runDummy() {
        MyCompression myCompression = new MyCompression();
        try {
            myCompression.readGrayscaleImage(new File("image1-onechannel.rgb"));
            myCompression.displayImage();
            //myCompression.displayImage();
            myCompression.initVectors();
            myCompression.compressImage();
            myCompression.displayNewImage();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
       // myCompression.displayImage();
    }

    public static void main(String[] args) {
        if (args.length != 3) {
            System.out.println("Usage: java MyCompression <input image> <vector size> <number of vectors>");
            System.out.println("Example: java MyCompression image1-onechannel.rgb 2 16");
            runDummy();
        } else {
            int vectorSize = Integer.parseInt(args[1]);
            int numVectors = Integer.parseInt(args[2]);
            MyCompression myCompression = new MyCompression(vectorSize, numVectors);
            try {
                myCompression.readGrayscaleImage(new File(args[0]));
                myCompression.displayImage();
                //myCompression.displayImage();
                myCompression.initVectors();
                myCompression.compressImage();
                myCompression.displayNewImage();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }

}

class ClusterComputation implements Runnable {

    private int clusterId;
    private MyCompression myCompression;

    public ClusterComputation(int clusterId, MyCompression myCompression) {
        this.clusterId = clusterId;
        this.myCompression = myCompression;
    }

    @Override
    public void run() {
        myCompression.runIteration(clusterId);
    }
    
}

class AggRGB {
    int r;
    int g;
    int b;
    int count;

    public AggRGB() {
        this.r = 0;
        this.g = 0;
        this.b = 0;
        this.count = 0;
    }

    public AggRGB(int r, int g, int b, int count) {
        this.r = r;
        this.g = g;
        this.b = b;
        this.count = count;
    }

    public void addPixel(int rgb) {
        this.r += (rgb >> 16) & 0xFF;
        this.g += (rgb >> 8) & 0xFF;
        this.b += rgb & 0xFF;
        this.count++;
    }

    public int getRGB() {
        if (this.count == 0) {
            return 0;
        }
        return (this.r / this.count) << 16 | (this.g / this.count) << 8 | (this.b / this.count);
    }

    public void clear() {
        this.r = 0;
        this.g = 0;
        this.b = 0;
        this.count = 0;
    }
}