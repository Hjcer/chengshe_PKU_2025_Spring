import pandas as pd

# 读取数据
dt = pd.read_excel('finance.xlsx', sheet_name='Sheet1')

# 删除“交易额”为空的数据
dt = dt.dropna(subset=['交易额'])

# 将“日期”列转为 datetime 类型
dt['日期'] = pd.to_datetime(dt['日期'])

# 按“日期”分组并求交易额总和
daily_total = dt.groupby('日期')['交易额'].sum().reset_index()
print(daily_total)

# 添加“星期”列（中文或英文二选一）
daily_total['星期'] = daily_total['日期'].dt.day_name()  # 英文
# daily_total['星期'] = daily_total['日期'].dt.dayofweek.map(['星期一','星期二','星期三','星期四','星期五','星期六','星期日'])  # 中文

# 找出交易额最小的三天，按交易额升序
daily_total = daily_total.sort_values(by='交易额').head(3)

# 输出格式化结果
for _, row in daily_total.iterrows():
    print(f"{row['日期'].date()} {int(row['交易额'])} {row['星期']}")
