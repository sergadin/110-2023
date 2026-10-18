import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('Копия populations.txt', delimiter='\t', skiprows=1)

years = data[:, 0]
hares = data[:, 1]
lynxes = data[:, 2]
carrots = data[:, 3]

true_value = hares[-1]

# ❌ "удаляем" его (делаем вид, что не знаем)
hares_known = hares[:-1]

# 📊 оценка (линейная экстраполяция)
estimate = hares_known[-1] + (hares_known[-1] - hares_known[-2])

# 📉 ошибка
error_ratio = abs(estimate - true_value) / true_value

print("Estimated:", estimate)
print("True:", true_value)
print("Error ratio:", error_ratio)