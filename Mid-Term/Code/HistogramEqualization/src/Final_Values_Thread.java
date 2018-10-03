public class Final_Values_Thread extends Thread {
    private final float[] b;
    private final int start_t;
    private final int end_t;
    private final float[] table;
    private final float[] newB;

    Final_Values_Thread(float[] b, int start_t, int end_t, float[] table, float[] newB){
        this.b = b;
        this.start_t = start_t;
        this.end_t = end_t;
        this.table = table;
        this.newB = newB;
    }

    public float[] getNewB() {
        return newB;
    }

    @Override
    public void run() {
        for (int i = start_t; i < end_t; i++) {
            int value = Math.max(0, Math.min(255, Math.round(b[i]*255)));
            newB[i] = Math.max(0, Math.min(1, table[value]));
        }
    }
}
