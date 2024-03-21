public class PerformanceFormulasHelper {

    public static float speedup(float T1, float TN) {
        return T1 / TN;
    }

    public static float speedup(float serialPart, int n) {
        return 1 / (serialPart + (1-serialPart)/n);
    }

    public static float efficiency(int T1, int TN, int n) {
        return speedup(T1, TN) / n;
    }

    public static float efficiency(float speedup, int n) {
        return speedup / n;
    }

    public static float time(int T1, float serialPart, int n) {
        return T1*(serialPart + ((1 - serialPart)/ n));
    }

    public static float cores(int T1, int TN, float serialPart) {
        return (1-serialPart)/(1/speedup(T1, (float) TN) - serialPart);
    }

    public static float cores(int serialPart, float speedup) {
        return (1-serialPart)/(1/speedup - serialPart);
    }

}
