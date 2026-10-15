using System;

namespace Mmind.Dl.Examples
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("MechMind DL SDK OpenCV Integration Example");
            Console.WriteLine("==========================================");

            try
            {
                int result = InferWithOpenCV.Run();
                Environment.Exit(result);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error: {ex.Message}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
                Environment.Exit(1);
            }
        }
    }
}
