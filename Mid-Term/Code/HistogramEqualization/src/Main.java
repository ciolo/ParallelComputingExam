import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.*;

public class Main {
    public static void main(String[] args) {

        boolean wenttocatch = false;
        Scanner in = new Scanner(System.in);

        String ser_par;
        boolean json = false;
        boolean serial = false;
        boolean parallel = false;
        do{
            System.out.print("Enter serial/parallel for serial or parallel implementation: ");
            if(in.hasNext()){
                ser_par = in.next();
                if (ser_par.equals("serial")) {
                    serial = true;
                    wenttocatch = true;
                } else if(ser_par.equals("parallel")) {
                    parallel = true;
                    wenttocatch = true;
                } else {
                    System.out.println("Enter a valid String: serial/parallel");
                }
            }else{
                in.nextLine();
                System.out.println("Enter a valid String: serial/parallel");
            }
        }while(!wenttocatch);

        int thread_num = 0;
        if(parallel) {
            wenttocatch = false;
            do{
                System.out.print("Enter number of threads: ");
                if(in.hasNextInt()){
                    thread_num = in.nextInt();
                    wenttocatch = true;
                }else{
                    in.nextLine();
                    System.out.println("Enter a valid Integer value");
                }
            }while(!wenttocatch);
        }

        System.out.print("\nEnter path of image: ");
        String image_path = in.next();
        /*String image_path = "images/input/big2.jpg";
        File folder = new File("images/input/");
        for(File im: folder.listFiles()) {
            System.out.println(im.getName());
        }*/

        File f1 = new File(image_path);

        BufferedImage img;
        try {
            img = ImageIO.read(f1);
        } catch (IOException e) {
            e.printStackTrace();
            img = new BufferedImage(10, 10, BufferedImage.TYPE_INT_RGB);
            System.out.println("Default image!");
        }

        HSB_Image hsb_img = new HSB_Image(img);

        long start;
        long duration_serial = 0;
        long duration_parallel = 0;
        float[] newV_serial = new float[256];
        float[] newV_parallel = new float[256];

        if (serial || !parallel) {
            //SERIAL
            //start timer
            start = System.nanoTime();
            newV_serial = Equalize_Serial.equalize(hsb_img.getB(), hsb_img.getNumPixels());
            duration_serial = System.nanoTime() - start;
            //stop timer
        }

        if (parallel || !serial) {

            //PARALLEL
            start = System.nanoTime();
            newV_parallel = Equalize_Parallel.equalize(hsb_img.getB(), hsb_img.getNumPixels(), thread_num);
            duration_parallel = System.nanoTime() - start;
            //stop timer
        }

        double seconds_serial = (double) duration_serial / 1000000000.0;

        String output = "{";

        if (serial || !parallel) {
            if (!json) {

                System.out.println("\nThe Serial equalization algorithm took average: " + seconds_serial + " s");

                hsb_img.setB(newV_serial);

                BufferedImage equalized = hsb_img.getRGBImage();

                File outputfile = new File("images/output/equalized_serial.png");
                try {
                    System.out.println("\nWriting output image...");
                    ImageIO.write(equalized, "png", outputfile);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            } else {
                output = output + "\"time_serial\": " + Double.toString(seconds_serial);
            }
        }

        double seconds_parallel = (double) duration_parallel / 1000000000.0;

        if (parallel || !serial) {
            if (!json) {
                System.out.println("\nThe Parallel equalization algorithm took average: " + seconds_parallel + " s");

                hsb_img.setB(newV_parallel);

                BufferedImage equalized_parallel = hsb_img.getRGBImage();

                File outputfile_parallel = new File("images/output/equalized_parallel.png");
                try {
                    System.out.println("\nWriting output image...");
                    ImageIO.write(equalized_parallel, "png", outputfile_parallel);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            } else {
                if (serial || !parallel) {
                    output = output + ", ";
                }
                output = output + "\"time_parallel\": " + Double.toString(seconds_parallel);
            }
        }

        output = output + "}";

        if (json) {
            System.out.println(output);
        }
    }
}