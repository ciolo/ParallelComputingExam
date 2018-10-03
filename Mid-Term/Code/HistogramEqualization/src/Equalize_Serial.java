
public class Equalize_Serial {
    static float[] equalize(float[] b, int size){

        int[] histogram = new int[256];
        int[] cumulative_histogram = new int[256];
        float[] table = new float[256];
        float[] newB = new float[size];


        //Histogram computation

        for (int i = 0; i < size; i++){
            int value = Math.max(0, Math.min(255, Math.round(b[i]*255)));
            histogram[value]++;
        }


        //Cumulative histogram computation (cumulative distribution function)
        //Every item in cumulative_histogram is the number of pixels with an intensity equal of lower than the index.
        cumulative_histogram[0] = histogram[0];
        //New value for each bin
        for(int i=1;i<256;i++){
            cumulative_histogram[i] = cumulative_histogram[i-1] + histogram[i];
            table[i] =  (float)(cumulative_histogram[i])/(float)size;
        }

        for (int i = 0; i<size; i++){
            int value = Math.max(0, Math.min(255, Math.round(b[i]*255)));
            newB[i] = Math.max(0, Math.min(1, table[value]));
        }

        return newB;
    }
}

