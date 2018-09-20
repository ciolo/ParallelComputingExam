
public class EqualizerSerial {
    static float[] equalize(float[] v, int size){


        //Histogram computation
        int[] histogram = new int[256];
        for (int i = 0; i < size; i++){
            int value = Math.max(0, Math.min(255, Math.round(v[i]*255)));
            histogram[value]++;
        }


        //Cumulative histogram computation (cumulative distribution function)
        //Every item in cumulative_histogram is the number of pixels with an intensity equal of lower than the index.
        int[] cumulative_histogram = new int[256];
        cumulative_histogram[0] = histogram[0];
        //New value for each bin
        float[] lookup = new float[256];
        for(int i=1;i<256;i++){
            cumulative_histogram[i] = cumulative_histogram[i-1] + histogram[i];
            lookup[i] =  (float)(cumulative_histogram[i])/(float)size;
        }

        float[] newV = new float[size];

        for (int i = 0; i<size; i++){
            int value = Math.max(0, Math.min(255, Math.round(v[i]*255)));
            newV[i] = Math.max(0, Math.min(1, lookup[value]));
        }

        return newV;
    }
}

