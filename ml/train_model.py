import numpy as np
from sklearn.ensemble import RandomForestClassifier
import joblib

X = np.random.rand(100, 2) * 100
y = (X[:, 0] + X[:, 1] > 100).astype(int)
model = RandomForestClassifier()
model.fit(X, y)
joblib.dump(model, 'ml/model.pkl')

