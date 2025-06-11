# ml/predict.py
import sys
import joblib
import numpy as np

dist = float(sys.argv[1])
hour = int(sys.argv[2])

model = joblib.load('ml/model.pkl')
X = np.array([[dist, hour]])
delay = model.predict(X)[0]

print(delay)
