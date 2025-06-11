# ml/train_model.py

import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import Pipeline
import joblib
import os

def train_model():
    try:
        df = pd.read_csv('travel_log.csv')
    except FileNotFoundError:
        print("❌ Error: 'travel_log.csv' not found.")
        return

    if df.empty or not {'distance', 'time_of_day', 'delay'}.issubset(df.columns):
        print("❌ Error: CSV must contain 'distance', 'time_of_day', and 'delay' columns.")
        return

    X = df[['distance', 'time_of_day']]
    y = df['delay']

    # Optional: Add a pipeline with normalization (good for ML performance)
    pipeline = Pipeline([
        ('scaler', StandardScaler()),
        ('regressor', LinearRegression())
    ])

    pipeline.fit(X, y)

    os.makedirs('ml', exist_ok=True)
    joblib.dump(pipeline, 'ml/model.pkl')
    print("✅ Model trained and saved to 'ml/model.pkl'")

if __name__ == "__main__":
    train_model()

