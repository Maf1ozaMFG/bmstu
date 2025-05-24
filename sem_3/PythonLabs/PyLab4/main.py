import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split

from input_module import read_csv_file, read_region
from logic_module import sort_region, evaluate_model, predict
from output_module import print_data_by_region, print_regions


def main():
    filepath = input("Enter filepath: ")

    data = read_csv_file(filepath)

    if data is None: return
    print_regions(data)

    region = read_region(data)

    data_sorted_region = sort_region(data, region)

    if data_sorted_region is None: return

    print_data_by_region(data_sorted_region)

    data_for_prediction = data_sorted_region[['year', 'death_rate']]

    data_on_x = data_for_prediction['year'].values

    data_on_y = data_for_prediction['death_rate'].values

    x_train, x_test, y_train, y_test = train_test_split(data_on_x.reshape(-1, 1), data_on_y, test_size=0.25, random_state=100)

    model = LinearRegression()
    model.fit(x_train, y_train)

    y_pred = model.predict(x_test)

    evaluate_model(y_test, y_pred)

    sorted_indices = x_test.flatten().argsort()
    x_test_sorted = x_test.flatten()[sorted_indices]
    y_pred_sorted = y_pred[sorted_indices]

    plt.figure(figure = (10, 6))
    sns.scatterplot(x = data_for_prediction['year'], y = data_for_prediction['death_rate'], color = 'blue', label = 'Actual data')
    plt.plot(x_test_sorted, y_pred_sorted, color = 'red', label = 'Regression line')
    plt.xlabel('Year')
    plt.ylabel('Birth Rate')
    plt.title('Prediction using Linear Regression')
    plt.legend()
    plt.show()

    user_year = int(input("Введите год для предсказания рождаемости: "))
    predicted_population = predict(user_year, model)
    print(f"Предсказанная рождаемость для {user_year}: {predicted_population:.2f}")

if __name__ == "__main__":
    main()

#C:\Program Files\PythonEducation\russian_demography.csv
#C:\Program Files\PythonEducation\empty_rows.csv