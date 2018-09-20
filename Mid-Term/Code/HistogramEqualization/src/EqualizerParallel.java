
public class EqualizerParallel {
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


    static float[] equalize(float[] v, int size, int thread_num){
        int threads = 0;
        //Number of threads the processor can handle at once
        //If the processor supports virtualization, this is 2*cores
        if (thread_num == 0) {
            threads = Runtime.getRuntime().availableProcessors();
        } else {
            threads = thread_num;
        }
        PartialLookupThread[] partialLookupThreads = new PartialLookupThread[threads];

        int size_per_thread = size/threads;
        int bins_per_thread = 256/threads;

        for (int i = 0; i < threads-1; i++) {
            int start_t = i*size_per_thread;
            int end_t = i*size_per_thread + size_per_thread;

            partialLookupThreads[i] = new PartialLookupThread(v, start_t, end_t, size);
        }

        partialLookupThreads[threads-1] = new PartialLookupThread(v, (threads-1)*size_per_thread, size, size);

        //launch threads
        launchThreads(threads, partialLookupThreads);
        //finished threads

        LookupAdder[] adders = new LookupAdder[threads];
        float[] lookup = new float[256];
        float [][] partialLookups = new float[threads][];

        for (int i = 0; i < threads; i++) {
            partialLookups[i] = partialLookupThreads[i].getPartialLookup();
        }

        for (int i = 0; i < threads-1; i++) {
            int start_h = i*bins_per_thread;
            int end_h = i*bins_per_thread + bins_per_thread;

            adders[i] = new LookupAdder(lookup, partialLookups, start_h, end_h, threads);
        }
        adders[threads-1] = new LookupAdder(lookup, partialLookups, (threads-1)*bins_per_thread, 256, threads);

        //launch threads
        launchThreads(threads, adders);
        //finished threads

        float[] newV = new float[size];

        EqualizedValuesCalculator[] equalizers = new EqualizedValuesCalculator[threads];

        for (int i = 0; i < threads-1; i++) {
            int start_t = i*size_per_thread;
            int end_t = i*size_per_thread + size_per_thread;

            equalizers[i] = new EqualizedValuesCalculator(v, start_t, end_t, lookup, newV);
        }

        equalizers[threads-1] = new EqualizedValuesCalculator(v, (threads-1)*size_per_thread, size, lookup, newV);

        //launch threads
        launchThreads(threads, equalizers);
        //finished threads

        return newV;
    }
}
