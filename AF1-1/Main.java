public class Main {
    public static void main(String[] args) {

        System.out.println(PerformanceFormulasHelper.speedup(0.32f, 2));
        System.out.println(PerformanceFormulasHelper.efficiency(
                PerformanceFormulasHelper.speedup(0.1F, 16), 16));
        System.out.println(PerformanceFormulasHelper.speedup(162.5f, 60.2f));
        System.out.println(PerformanceFormulasHelper.cores(60, 6, 0.05f));
    }
}
