
public class Equalize_Parallel {
    private static boolean launchThreads(int thread_number, Thread[] threads){
        for (int i = 0; i < thread_number; i++) {
            threads[i].start();
        }

        for (int i = 0; i < thread_number; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                System.out.println("Exception has " +
                        "been caught" + e);
                return false;
            }
        }

        return true;
    }


    static float[] equalize(float[] b, int size, int thread_num){
        int threads = 0;
        //Number of threads the processor can handle at once
        //If the processor supports virtualization, this is 2*cores
        if (thread_num == 0) {
            threads = Runtime.getRuntime().availableProcessors();
        } else {
            threads = thread_num;
        }
        Partial_Table_Thread[] partialTableThreads = new Partial_Table_Thread[threads];

        int size_per_thread = size/threads;
        int bins_per_thread = 256/threads;

        for (int i = 0; i < threads-1; i++) {
            int start_t = i*size_per_thread;
            int end_t = i*size_per_thread + size_per_thread;

            partialTableThreads[i] = new Partial_Table_Thread(b, start_t, end_t, size);
        }

        partialTableThreads[threads-1] = new Partial_Table_Thread(b, (threads-1)*size_per_thread, size, size);

        //launch threads
        launchThreads(threads, partialTableThreads);
        //finished threads

        Table_Adder_Thread[] adders = new Table_Adder_Thread[threads];
        float[] table = new float[256];
        float [][] partialTable = new float[threads][];

        for (int i = 0; i < threads; i++) {
            partialTable[i] = partialTableThreads[i].getPartialTable();
        }

        for (int i = 0; i < threads-1; i++) {
            int start_h = i*bins_per_thread;
            int end_h = i*bins_per_thread + bins_per_thread;

            adders[i] = new Table_Adder_Thread(table, partialTable, start_h, end_h, threads);
        }
        adders[threads-1] = new Table_Adder_Thread(table, partialTable, (threads-1)*bins_per_thread, 256, threads);

        //launch threads
        launchThreads(threads, adders);
        //finished threads

        float[] newB = new float[size];

        Final_Values_Thread[] equalizers = new Final_Values_Thread[threads];

        for (int i = 0; i < threads-1; i++) {
            int start_t = i*size_per_thread;
            int end_t = i*size_per_thread + size_per_thread;

            equalizers[i] = new Final_Values_Thread(b, start_t, end_t, table, newB);
        }

        equalizers[threads-1] = new Final_Values_Thread(b, (threads-1)*size_per_thread, size, table, newB);

        //launch threads
        launchThreads(threads, equalizers);
        //finished threads

        return newB;
    }
}
