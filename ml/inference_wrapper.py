import joblib
import os

model_path = os.path.join(os.path.dirname(__file__), 'model.pkl')
model = joblib.load(model_path)

def predict_class(f1, f2):
    return int(model.predict([[f1, f2]])[0])

