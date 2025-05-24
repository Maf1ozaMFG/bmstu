import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d, CubicSpline
from typing import Callable


class Interpolator:
    def __init__(self, func: Callable, x_start: float, x_end: float, step: float):
        self.func = func
        self.x_values = np.arange(x_start, x_end, step)
        self.y_values = self.func(self.x_values)

        if len(self.x_values) < 4:
            raise ValueError("Недостаточно точек для всех методов интерполяции. Увеличьте диапазон или уменьшите шаг.")

        self.methods = {}
        try:
            self.methods['linear'] = interp1d(self.x_values, self.y_values, kind='linear')
            self.methods['quadratic'] = interp1d(self.x_values, self.y_values, kind='quadratic')
            self.methods['cubic'] = interp1d(self.x_values, self.y_values, kind='cubic')
            self.methods['spline'] = CubicSpline(self.x_values, self.y_values)
        except Exception as e:
            print(f"Ошибка при создании метода интерполяции: {e}")

    def interpolate(self, x_point: float, method: str) -> float:
        if not (self.x_values[0] <= x_point <= self.x_values[-1]):
            raise ValueError("Точка вне диапазона известных данных.")
        interpolated_value = self.methods[method](x_point)
        real_value = self.func(x_point)
        error = abs(real_value - interpolated_value)
        print(f"Метод: {method.capitalize()}\n"
              f"Интерполированное значение: {interpolated_value}\n"
              f"Реальное значение: {real_value}\n"
              f"Ошибка интерполяции: {error}\n")
        return interpolated_value

    def plot(self):
        x_dense = np.linspace(self.x_values[0], self.x_values[-1], 500)
        num_methods = len(self.methods)

        plt.figure(figsize=(12, 8))

        for i, (method_name, method) in enumerate(self.methods.items(), 1):
            plt.subplot(2, 2, i)
            plt.plot(x_dense, self.func(x_dense), label="Original Function", color="black", linestyle="--")
            plt.plot(x_dense, method(x_dense), label=f"{method_name.capitalize()} Interpolation")

            plt.scatter(self.x_values, self.y_values, color="red", label="Data Points")

            plt.title(f"{method_name.capitalize()} Interpolation")
            plt.xlabel("x")
            plt.ylabel("f(x)")
            plt.legend()
            plt.grid(True)

        plt.tight_layout()
        plt.show()


def main():

    #np.sin(x) + x**2
    #1/x + 1/x**3

    user_func_str = input("Введите функцию от x: ")
    x_start = float(input("Введите начало диапазона x: "))
    x_end = float(input("Введите конец диапазона x: "))
    step = float(input("Введите шаг разбиения: "))

    user_func = lambda x: eval(user_func_str)

    try:
        interpolator = Interpolator(user_func, x_start, x_end, step)
    except ValueError as e:
        print(e)
        return

    interpolator.plot()

    x_point = float(input("Введите значение x для интерполяции: "))
    method = input("Выберите метод интерполяции (linear, quadratic, cubic, spline): ").strip().lower()

    try:
        interpolator.interpolate(x_point, method)
    except ValueError as e:
        print(e)


if __name__ == "__main__":
    main()