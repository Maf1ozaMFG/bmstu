using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace LinearAlgebra
{
    public class MathVector : IMathVector
    {
        private double[] _vector;
        public MathVector(int dimensions)
        {
            ArgumentOutOfRangeException.ThrowIfNegativeOrZero(dimensions);

            Dimensions = dimensions;
            _vector = new double[Dimensions];
        }
        
        public MathVector(double[] vector)
        {
            ArgumentNullException.ThrowIfNull(vector);
            if (vector.Length == 0) throw new ArgumentException("Vector have to contain at least 1 element", nameof(vector));

            Dimensions = vector.Length;
            _vector = (double[])vector.Clone();
        }

        public int Dimensions { get; }

        public double this[int i]
        {
            get
            {
                if (i < 0 || i >= Dimensions) throw new IndexOutOfRangeException($"Index {i} is out of range");
                return _vector[i];
            }
            set
            {
                if (i < 0 || i >= Dimensions) throw new IndexOutOfRangeException($"Index {i} is out of range");
                _vector[i] = value;
            }
        }

        public IEnumerator GetEnumerator() => _vector.GetEnumerator();

        public double Length
        {
            get
            {
                double len = 0;
                foreach (var elem in _vector)
                {
                    len += elem * elem;
                }
                return Math.Sqrt(len);
            }
        }

        public IMathVector SumNumber(double number) {
            var newVector = _vector.Select(x => x + number).ToArray();
            return new MathVector(newVector);
        }


        public IMathVector MultiplyNumber(double number)
        {
            var newVector = _vector.Select(x => x * number).ToArray();
            return new MathVector(newVector);
        }


        public IMathVector Sum(IMathVector vector) {
            DimensionCheck(vector);
            var newVector = new double[Dimensions];
            for (var i = 0; i < Dimensions; i++)
            {
                newVector[i] = this[i] + vector[i];
            }
            return new MathVector(newVector);
        }


        public IMathVector Multiply(IMathVector vector)
    {
        DimensionCheck(vector);
        var newVector = new double[Dimensions];
        for (var i = 0; i < Dimensions; i++)
        {
            newVector[i] = this[i] * vector[i];
        }
        return new MathVector(newVector);
    }

        public double ScalarMultiply(IMathVector vector)
        {
            DimensionCheck(vector);
            double scalar = 0;
            for (var i = 0; i < Dimensions; i++)
            {
                scalar += this[i] * vector[i];
            }
            return scalar;
        }

        public double CalculateDistance(IMathVector vector)
        {
            DimensionCheck(vector);
            return Math.Sqrt(Enumerable.Range(0, Dimensions).Sum(i => Math.Pow(this[i] - vector[i], 2)));
        }

        public override bool Equals(object obj)
        {
            if (obj is not MathVector other || Dimensions != other.Dimensions) return false;

            for (var i = 0; i < Dimensions; i++)
            {
                if (Math.Abs(this[i] - other[i]) > 1e-9)
                    return false;
            }
            return true;
        }


        public static IMathVector operator +(MathVector vector, double number)
        {
            return vector.SumNumber(number);
        }

       
        public static IMathVector operator +(MathVector vector1, IMathVector vector2)
        {
            if (vector1.Dimensions != vector2.Dimensions) throw new ArgumentException("Vectors must have same dimensions");
            return vector1.Sum(vector2);
        }
        
        public static IMathVector operator -(MathVector vector, double number)
        {
            return vector.SumNumber(-number);
        }
        
        public static IMathVector operator -(MathVector vector1, IMathVector vector2)
        {
            if (vector1.Dimensions != vector2.Dimensions) throw new ArgumentException("Vectors must have same dimensions");
            return vector1.Sum(vector2.MultiplyNumber(-1));
        }

        
        public static IMathVector operator *(MathVector vector, double number)
        {
            return vector.MultiplyNumber(number);
        }

        
        public static IMathVector operator *(MathVector vector1, IMathVector vector2)
        {
            if (vector1.Dimensions != vector2.Dimensions) throw new ArgumentException("Vectors must have same dimensions");
            return vector1.Multiply(vector2);
        }


        public static IMathVector operator /(MathVector vector, double number)
        {
            if (number == 0) throw new DivideByZeroException();

            var resultArray = new double[vector.Dimensions];
            for (int i = 0; i < vector.Dimensions; i++)
            {
                resultArray[i] = vector[i] / number;
            }

            return new MathVector(resultArray);
        }

        public static bool operator ==(MathVector left, MathVector right)
        {
            if (left is null && right is null) return true;
            if (left is null || left is null) return false;

            return left.Equals(right);
        }

        public static bool operator !=(MathVector left, MathVector right)
        {
            return !(left == right);
        }


        public static IMathVector operator /(MathVector vector1, IMathVector vector2)
        {
            if (vector2 == null) throw new ArgumentException("Vector 2 is null");
            if (vector1.Dimensions != vector2.Dimensions) throw new ArgumentException("Vectors must have same dimensions");
            
            var vector3 = new MathVector(vector1.Dimensions);
            for (var i = 0; i < vector1.Dimensions; i++)
            {
                if (vector2[i] == 0) throw new DivideByZeroException("There was a zero in second vector");
                vector3[i] = vector1[i] / vector2[i];
            }
            return vector3;
        }

        
        public static double operator %(MathVector vector1, IMathVector vector2)
        {
            if (vector1.Dimensions != vector2.Dimensions) throw new ArgumentException("Vectors must have same dimensions");
            return vector1.ScalarMultiply(vector2);
        }

        private void DimensionCheck(IMathVector vector)
        {
            if (Dimensions != vector.Dimensions) throw new ArgumentException("Vectors must have same lenght");
            if (Dimensions == 0) throw new ArgumentException("Vector with dimension 0 can't be");
        }
    }
}