import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split


def load_data(filepath):
    try:
        data = pd.read_csv(filepath)
        return data
    except Exception as e:
        print(f"Error loading file: {e}")
        return None


def preprocess_data(data):
    data = data[['year', 'birth_rate']].dropna()
    return data


def perform_regression(data):
    x = data['year'].values.reshape(-1, 1)
    y = data['birth_rate'].values

    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=42)

    model = LinearRegression()
    model.fit(x_train, y_train)

    y_pred = model.predict(x_test)

    return model, x_test, y_test, y_pred


def plot_regression(model, data):
    plt.scatter(data['year'], data['birth_rate'], color='blue', label='Real data')

    plt.plot(data['year'], model.predict(data['year'].values.reshape(-1, 1)), color='red', label='Linear regression')

    plt.xlabel('year')
    plt.ylabel('birth_rate')
    plt.title('Linear Regression on Russian Demography Data')
    plt.legend()
    plt.show()

def main():
    filepath = input("Enter filepath for dataset: ")

    data = load_data(filepath)
    if data is None:
        return

    data = preprocess_data(data)

    model, x_test, y_test, y_pred = perform_regression(data)

    plot_regression(model, data)

    year = float(input("Enter the year to predict birth rate: "))
    pred_birth_rate = model.predict(np.array([[year]]))
    print(f"Predicted birth rate for {year}: {pred_birth_rate[0]}")


if __name__ == "__main__":
    main()

#C:\Program Files\PythonEducation\russian_demography.csv