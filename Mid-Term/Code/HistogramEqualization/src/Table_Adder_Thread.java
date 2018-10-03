public class Table_Adder_Thread extends Thread{
    private final float[] table;
    private final float[][] partial_table;
    private final int start;
    private final int end;
    private final int num_partials;

    public float[] getTable() {
        return table;
    }

    Table_Adder_Thread(float [] table, float [][] partial_table, int start, int end, int num_partials){
        this.table = table;
        this.partial_table = partial_table;
        this.start = start;
        this.end = end;
        this.num_partials = num_partials;
    }

    @Override
    public void run() {
        for (int i = start; i < end; i++) {
            float tot = 0;
            for (int j = 0; j < num_partials; j++) {
                tot += partial_table[j][i];
            }

            table[i] = tot;
        }
    }
}