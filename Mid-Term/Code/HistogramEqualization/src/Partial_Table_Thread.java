public class Partial_Table_Thread extends Thread {
    private float[] table;
    private final float[] b;
    private final int start;
    private final int end;
    private final int size;

    public float[] getPartialTable() {
        return table;
    }

    Partial_Table_Thread(float [] b, int start, int end, int size){
        this.b = b;
        this.start = start;
        this.end = end;
        this.size = size;
        this.table = new float[256];
    }

    @Override
    public void run() {
        //Histogram computation
        int[] histogram = new int[256];
        for (int i = start; i < end; i++){
            int value = Math.max(0, Math.min(255, Math.round(b[i]*255)));
            histogram[value]++;
        }

        //Cumulative histogram computation (cumulative distribution function)
        int[] cumulative_histogram = new int[256];
        cumulative_histogram[0] = histogram[0];
        table[0] =  ((float)1/(float)255)*(float)((cumulative_histogram[0]*255.0)/(float)size);
        for(int i=1;i<256;i++){
            cumulative_histogram[i] = cumulative_histogram[i-1] + histogram[i];
            //New value for each bin
            table[i] =  (float)(cumulative_histogram[i])/(float)size;
        }
    }
}

