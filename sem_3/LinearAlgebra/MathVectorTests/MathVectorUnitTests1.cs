using LinearAlgebra;


namespace LinearAlgebra.Tests
{
    public class MathVectorTests
    {
        [Fact]
        public void TestDimensions()
        {
            var vector = new MathVector(new double[] { 1, 0, 3, 5 });

            int expected = 4;
            int result = vector.Dimensions;

            Assert.Equal(expected, result);
        }

        [Fact]
        public void TestIndex()
        {
            var vector = new MathVector(new double[] { 1, 0, 3, 5 });

            int i = 1;
            double expected = 0;
            double result = vector[i];

            Assert.Equal(expected, result);
        }

        [Fact]
        public void TestIndexSet()
        {
            var vector = new MathVector(new double[] { 1, 0, 3, 5 });

            vector[1] = 5;
            var expected = new MathVector(new double[] { 1, 5, 3, 5 });


            Assert.True(expected == vector);
        }

        [Fact]
        public void TestIndexSetException()
        {
            var vector = new MathVector(new double[] { 1, 0, 3, 5 });

            int i = -1;

            Assert.Throws<IndexOutOfRangeException>(() => vector[i] = 6);
        }

        [Fact]
        public void TestIndexSetExceptionPlus()
        {
            var vector = new MathVector(new double[] { 1, 0, 3, 5 });

            int i = 100;

            Assert.Throws<IndexOutOfRangeException>(() => vector[i] = 6);
        }

        [Fact]
        public void TestIndexExceptionMinus()
        {
            var vector = new MathVector(new double[] { 1, 0, 3, 5 });

            int i = -1;

            Assert.Throws<IndexOutOfRangeException>(() => vector[i]);
        }


        [Fact]
        public void TestIndexMinusExceptionPlus()
        {
            var vector = new MathVector(new double[] { 1, 0, 3, 5 });

            int i = 100;

            Assert.Throws<IndexOutOfRangeException>(() => vector[i]);
        }

        [Fact]
        public void TestInverseOperations()
        {
            var vector1 = new MathVector(new double[] { 1, 2, 3 });
            var vector2 = new MathVector(new double[] { 4, 5, 6 });

            var sum = (MathVector)(vector1 + vector2);

            var result = (MathVector)(sum - vector2);

            Assert.True(vector1 == result);
        }


        [Fact]
        public void TestLengthPositive()
        {
            var vector = new MathVector(new double[] { 1, 0, 3, 5 });

            double expected = 5.9160797;
            double result = vector.Length;

            Assert.Equal(expected, result, 0.0000001);
        }

        [Fact]
        public void TestLengthNegative()
        {
            var vector = new MathVector(new double[] { -5 });

            double expected = 5;
            double result = vector.Length;

            Assert.Equal(expected, result);
        }

        [Fact]
        public void TestLenghtZero()
        {
            var zeroVector = new MathVector(new double[] { 0, 0, 0 });

            double expected = 0;
            double result = zeroVector.Length;

            Assert.Equal(expected, result);
        }


        [Fact]
        public void TestSumNumberPlus()
        {
            var vector = new MathVector(new double[] { 1, 0, 3, 5 });
            var expected = new MathVector(new double[] { 4, 3, 6, 8 });

            var result = (MathVector)vector.SumNumber(3);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestSumNumberFalse()
        {
            var vector = new MathVector(new double[] { 1, 4 });
            var expected = new MathVector(new double[] { 5, 7 });

            var result = (MathVector)vector.SumNumber(3);

            Assert.False(expected == result);
        }

        [Fact]
        public void TestSumNumberMinus()
        {
            var vector = new MathVector(new double[] { 1, 4 });
            var expected = new MathVector(new double[] { -2, 1 });

            var result = (MathVector)vector.SumNumber(-3);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestSumNumberLargeValues()
        {
            var vector = new MathVector(new double[] { 1e9, -1e9 });
            var expected = new MathVector(new double[] { 1e9 + 2, -1e9 + 2 });

            var result = (MathVector)(vector + 2);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestMultiplyNumberNegative()
        {
            var vector = new MathVector(new double[] { 1, 4 });
            var expected = new MathVector(new double[] { -1, -4 });

            var result = (MathVector)vector.MultiplyNumber(-1);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestMultiplyNumberNull()
        {
            var vector = new MathVector(new double[] { 1, 4 });
            var expected = new MathVector(new double[] { 0, 0 });

            var result = (MathVector)vector.MultiplyNumber(0);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestMultiplyNumberPositive()
        {
            var vector = new MathVector(new double[] { 1, 4, 2 });
            var expected = new MathVector(new double[] { 3, 12, 6 });

            var result = (MathVector)vector.MultiplyNumber(3);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestMultiplyNumberFalse()
        {
            var vector = new MathVector(new double[] { 1, 4, 2 });
            var expected = new MathVector(new double[] { 0, 12, 6 });

            var result = (MathVector)vector.MultiplyNumber(3);

            Assert.False(expected == result);
        }

        [Fact]
        public void TestSum()
        {
            var vector = new MathVector(new double[] { 1, 4, 2 });
            var vect2 = new MathVector(new double[] { 2, 3, 5 });

            var expected = new MathVector(new double[] { 3, 7, 7 });

            var result = (MathVector)vector.Sum(vect2);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestSumException()
        {
            var vector = new MathVector(new double[] { 1, 4, 2 });
            var vect2 = new MathVector(new double[] { 2, 3 });

            Assert.Throws<ArgumentException>(() => (MathVector)vector.Sum(vect2));
        }

        [Fact]
        public void TestMultiplyTrue()
        {
            var vector = new MathVector(new double[] { 1, 4, 2 });
            var vect2 = new MathVector(new double[] { 2, 3, 5 });

            var expected = new MathVector(new double[] { 2, 12, 10 });

            var result = (MathVector)vector.Multiply(vect2);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestMultiplyFalse()
        {
            var vector = new MathVector(new double[] { 1, 4, 2 });
            var vect2 = new MathVector(new double[] { 2, 3, 5 });

            var expected = new MathVector(new double[] { 2, 12, 1 });

            var result = (MathVector)vector.Multiply(vect2);

            Assert.False(expected == result);
        }

        [Fact]
        public void TestMultiplyException()
        {
            var vector = new MathVector(new double[] { 1, 4, 2 });
            var vect2 = new MathVector(new double[] { 2, 3 });

            Assert.Throws<ArgumentException>(() => (MathVector)vector.Multiply(vect2));
        }

        [Fact]
        public void TestOperatorDivideNumberZeroException()
        {
            var vector = new MathVector(new double[] { 6, 4, 2 });

            Assert.Throws<DivideByZeroException>(() => (MathVector)vector / 0);
        }

        [Fact]
        public void TestScalar()
        {
            var vector = new MathVector(new double[] { 6, 4, 2 });
            var vect2 = new MathVector(new double[] { 3, 2, 0 });

            double result = 26;

            double expected = vector.ScalarMultiply(vect2);

            Assert.Equal(expected, result);
        }

        [Fact]
        public void TestScalarException()
        {
            var vector = new MathVector(new double[] { 6, 4, 2 });
            var vect2 = new MathVector(new double[] { 3, 2 });

            Assert.Throws<ArgumentException>(() => vector.ScalarMultiply(vect2));
        }

        [Fact]
        public void TestCalcDistance()
        {
            var vector = new MathVector(new double[] { 6, 4, 2 });
            var vect2 = new MathVector(new double[] { 3, 2, 4 });

            double result = 4.1231056;

            double expected = vector.CalculateDistance(vect2);

            Assert.Equal(expected, result, 0.0000001);
        }

        [Fact]
        public void TestDistanceToSelf()
        {
            var vector = new MathVector(new double[] { 3, 4, 5 });

            double expected = 0;
            double result = vector.CalculateDistance(vector);

            Assert.Equal(expected, result);
        }


        [Fact]
        public void TestCalcDistanceDiffLengthException()
        {
            var vector = new MathVector(new double[] { 6, 4, 2 });
            var vect2 = new MathVector(new double[] { 3, 2 });

            Assert.Throws<ArgumentException>(() => vector.CalculateDistance(vect2));
        }

        [Fact]
        public void TestOperatorPlusNumber()
        {
            var vector = new MathVector(new double[] { 1, 0, 3, 5 });

            var expected = new MathVector(new double[] { 4, 3, 6, 8 });

            var result = (MathVector)(vector + 3);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestOperatorPlusVector()
        {
            var vector = new MathVector(new double[] { 4, 4, 2 });
            var vect2 = new MathVector(new double[] { 3, 2, 4 });

            var expected = new MathVector(new double[] { 7, 6, 6 });

            var result = (MathVector)(vector + vect2);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestOperatorMinusNumber()
        {
            var vector = new MathVector(new double[] { 1, 0, 3, 5 });

            var expected = new MathVector(new double[] { 0, -1, 2, 4 });

            var result = (MathVector)(vector - 1);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestOperatorMinusVector()
        {
            var vector = new MathVector(new double[] { 6, 4, 2 });
            var vect2 = new MathVector(new double[] { 3, 2, 4 });

            var expected = new MathVector(new double[] { 3, 2, -2 });

            var result = (MathVector)(vector - vect2);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestOperatorMultiplyNumber()
        {
            var vector = new MathVector(new double[] { 1, 0, 3, 5 });

            var expected = new MathVector(new double[] { 3, 0, 9, 15 });

            var result = (MathVector)(vector * 3);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestOperatorMultiplyVector()
        {
            var vector = new MathVector(new double[] { 6, 4, 2 });
            var vect2 = new MathVector(new double[] { 3, 2, 4 });

            var expected = new MathVector(new double[] { 18, 8, 8 });

            var result = (MathVector)(vector * vect2);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestOperatorDivideNumber()
        {
            var vector = new MathVector(new double[] { 9, 0, 3, 12 });

            var expected = new MathVector(new double[] { 3, 0, 1, 4 });

            var result = (MathVector)(vector / 3);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestOperatorDivideVector()
        {
            var vector = new MathVector(new double[] { 6, 4, 2 });
            var vect2 = new MathVector(new double[] { 3, 2, 4 });

            var expected = new MathVector(new double[] { 2, 2, 0.5 });

            var result = (MathVector)(vector / vect2);

            Assert.True(expected == result);
        }

        [Fact]
        public void TestOperatorDivideBySelf()
        {
            var vector = new MathVector(new double[] { 2, 4, 8 });
            var expected = new MathVector(new double[] { 1, 1, 1 });

            var result = (MathVector)(vector / vector);

            Assert.True(expected == result);
        }


        [Fact]
        public void TestOperatorDivideException()
        {
            var vector = new MathVector(new double[] { 1, 4, 2 });
            var vect2 = new MathVector(new double[] { 2, 3 });

            Assert.Throws<ArgumentException>(() => (MathVector)vector / vect2);
        }

        [Fact]
        public void TestOperatorDivideByZeroException()
        {
            var vector = new MathVector(new double[] { 6, 4, 2 });
            var vect2 = new MathVector(new double[] { 3, 2, 0 });

            Assert.Throws<DivideByZeroException>(() => (MathVector)vector / vect2);
        }

        [Fact]
        public void TestOperatorDivideByNullException()
        {
            var vector1 = new MathVector(new double[] { 1, 2, 3 });
            IMathVector vector2 = null;

            Assert.Throws<ArgumentException>(() => (MathVector)vector1 / (MathVector)vector2);

        }

        [Fact]
        public void TestOperatorScalar()
        {
            var vector = new MathVector(new double[] { 6, 4, 2 });
            var vect2 = new MathVector(new double[] { 3, 2, 0 });

            double result = 26;

            double expected = vector % vect2;

            Assert.Equal(expected, result);
        }

        [Fact]
        public void TestEmptyVectorInitialization()
        {
            Assert.Throws<ArgumentException>(() => new MathVector(new double[] { }));
        }

        [Fact]
        public void TestNegativeDimensions()
        {
            Assert.Throws<ArgumentOutOfRangeException>(() => new MathVector(-5));
        }

        [Fact]
        public void TestZeroDimensions()
        {
            Assert.Throws<ArgumentOutOfRangeException>(() => new MathVector(0));
        }

        [Fact]
        public void TestEqualsTrue()
        {
            var vector1 = new MathVector(new double[] { 1, 2, 3 });
            var vector2 = new MathVector(new double[] { 1, 2, 3 });

            Assert.True(vector1 == vector2);
        }

        [Fact]
        public void TestEqualsFalse()
        {
            var vector1 = new MathVector(new double[] { 1, 2, 3 });
            var vector2 = new MathVector(new double[] { 3, 2, 1 });

            Assert.False(vector1 == vector2);
        }
    }
}