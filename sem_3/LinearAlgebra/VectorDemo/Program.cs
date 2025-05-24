using LinearAlgebra;

internal class Program
{
    private static void Main(string[] args)
    {
        void PrintVector(IMathVector firstVector)
        {
            Console.Write("{ " + $"{firstVector[0]}");
            for (var i = 1; i < firstVector.Dimensions; i++)
            {
                Console.Write($", {firstVector[i]}");
            }
            Console.WriteLine(" }");
        }

        var examples = new Example[]
        {
        () =>
        {
            Console.WriteLine("\nLength Example\n");
            var mas = new double[]{ 3, 4, 12};
            var firstVector = new MathVector(mas);
            PrintVector(firstVector);
            Console.WriteLine($"Length = {firstVector.Length}");
        },

        ()=>
        {
            Console.WriteLine("\nSumNumber Example\n");
            var firstVector = new MathVector(new double[]{ 1, 5, 15, 19});
            PrintVector(firstVector);
            Console.Write("\t\t + 8 = ");
            PrintVector(firstVector.SumNumber(8));
        },

        ()=>
        {
            Console.WriteLine("\nMultiply Example\n");
            var firstVector = new MathVector(new double[]{ 2, 4, 8, 16});
            PrintVector(firstVector);
            Console.Write("\t\t * 8 = ");
            PrintVector(firstVector.MultiplyNumber(8));
        },

        ()=>
        {
            Console.WriteLine("\nSum Example\n");
            var firstVector = new MathVector(new double[]{ 4, 5, 6, 7});
            var secondVector = new MathVector(new double[]{7, 6, 5, 4});
            PrintVector(firstVector);
            Console.WriteLine("+");
            PrintVector(secondVector);
            Console.WriteLine("= ");
            PrintVector(firstVector.Sum(secondVector));
        },

        ()=>
        {
            Console.WriteLine("\nMultilply Example\n");
            var firstVector = new MathVector(new double[]{ 10, 45, 15});
            var secondVector = new MathVector(new double[]{2, 2, 2});
            PrintVector(firstVector);
            Console.WriteLine("*");
            PrintVector(secondVector);
            Console.WriteLine("= ");
            PrintVector(firstVector.Sum(secondVector));
        },

        ()=>
        {
            Console.WriteLine("\nScalarMultiply Example\n");
            var firstVector = new MathVector(new double[]{ 2, 8, 10});
            var secondVector = new MathVector(new double[]{1, 4, 5});
            PrintVector(firstVector);
            Console.WriteLine("*|");
            PrintVector(secondVector);
            Console.WriteLine("=");
            Console.WriteLine(firstVector.ScalarMultiply(secondVector));
        },

        ()=>
        {
            Console.WriteLine("\nCalcDistance Example\n");
            var firstVector = new MathVector(new double[]{-2, 1});
            var secondVector = new MathVector(new double[]{1, 5});
            PrintVector(firstVector);
            PrintVector(secondVector);
            Console.WriteLine($"distance = {firstVector.ScalarMultiply(secondVector)}");
        },

        ()=>
        {
            Console.WriteLine("\nOperator + Example\n");
            var firstVector = new MathVector(new double[]{6, 7, 14});
            var secondVector = new MathVector(new double[]{6, 2, 1});
            PrintVector(firstVector);
            PrintVector(secondVector);
            Console.Write("firstVector + secondVector = ");
            PrintVector(firstVector + secondVector);
            Console.Write("firstVector + 15 = ");
            PrintVector(firstVector + 15);
        },

        ()=>
        {
            Console.WriteLine("\nOperator - Example\n");
            var firstVector = new MathVector(new double[]{10, 40, 12});
            var secondVector = new MathVector(new double[]{6, 2, 1});
            PrintVector(firstVector);
            PrintVector(secondVector);
            Console.Write("firstVector - secondVector = ");
            PrintVector(firstVector - secondVector);
            Console.Write("firstVector - 4 = ");
            PrintVector(firstVector - 4);
        },

        ()=>
        {
            Console.WriteLine("\nOperator * Example\n");
            var firstVector = new MathVector(new double[]{65, 34, 11});
            var secondVector = new MathVector(new double[]{3, 2, 5});
            PrintVector(firstVector);
            PrintVector(secondVector);
            Console.Write("firstVector * secondVector = ");
            PrintVector(firstVector * secondVector);
            Console.Write("firstVector * 2 = ");
            PrintVector(firstVector * 2);
        },

        ()=>
        {
            Console.WriteLine("\nOperator / Example\n");
            var firstVector = new MathVector(new double[]{38, 90, 4});
            var secondVector = new MathVector(new double[]{-2, 5, -5});
            PrintVector(firstVector);
            PrintVector(secondVector);
            Console.Write("firstVector / secondVector = ");
            PrintVector(firstVector / secondVector);
            Console.Write("firstVector / 4 = ");
            PrintVector(firstVector / 4);
        },

        ()=>
        {
            Console.WriteLine("\nOperator % Example\n");
            var firstVector = new MathVector(new double[]{ 2, -8, 10});
            var secondVector = new MathVector(new double[]{1, 4, -5});
            PrintVector(firstVector);
            PrintVector(secondVector);
            Console.WriteLine($"firstVector % secondVector = {firstVector % secondVector}");

        }
        };

        foreach (var example in examples)
        {
            example();
        }
    }

    delegate void Example();
}
