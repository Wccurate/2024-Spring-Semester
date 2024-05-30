import pandas as pd

data = pd.read_csv('titanic.csv')

json_path = 'titanic.json'
data.to_json(json_path, orient='records', lines=True)

print(f"JSON文件已保存到: {json_path}")
