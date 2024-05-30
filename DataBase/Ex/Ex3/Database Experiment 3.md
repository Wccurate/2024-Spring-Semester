# Database Experiment 3

## HDFS Distribution File System



![image-20240430103436340](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240430103436340.png)

![image-20240430111705877](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240430111705877.png)

![image-20240430111744867](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240430111744867.png)

![image-20240430111835986](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240430111835986.png)

![image-20240430112017749](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240430112017749.png)

![image-20240430110845154](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240430110845154.png)

## Upload titanic.json

![image-20240430112354790](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240430112354790.png)

## Query Sentences

```sql
SELECT COLUMN_NAME
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_SCHEMA = 'sparktest' AND TABLE_NAME = 'titanic';
```

### Statistic for Survivals

```sql
select count(*) from titanic where Survived=1;
```

Result:

![image-20240430113646722](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240430113646722.png)

Total survivals up to 342 among 891;

### Search portion of male and female in survivals and deceaseds

```sql
SELECT 
    Sex,
    Survived,
    COUNT(*) AS Count,
    ROUND((COUNT(*) * 100.0 / SUM(COUNT(*)) OVER (PARTITION BY Sex)), 2) AS Percentage
FROM 
    titanic
GROUP BY 
    Sex, 
    Survived;
```

Result:

![image-20240430114248296](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240430114248296.png)

(female, 1) stands for survival women

(female, 0) stands for deceased women

so as to male

### statistic data for class variance

```sql
SELECT 
    Pclass,
    COUNT(CASE WHEN Survived = 1 THEN 1 ELSE NULL END) AS Survived_Count,
    COUNT(*) AS Total_Count,
    ROUND((COUNT(CASE WHEN Survived = 1 THEN 1 ELSE NULL END) * 100.0 / COUNT(*)), 2) AS Survival_Rate
FROM 
    titanic
GROUP BY 
    Pclass;
```

Result:

![image-20240430115112366](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240430115112366.png)

(pclass, survivals, total,portion)

### statistic data for age variance

```sql
SELECT 
    Age_Group,
    COUNT(CASE WHEN Survived = 1 THEN 1 ELSE NULL END) AS Survived_Count,
    COUNT(*) AS Total_Count,
    ROUND((COUNT(CASE WHEN Survived = 1 THEN 1 ELSE NULL END) * 100.0 / COUNT(*)), 2) AS Survival_Rate
FROM 
    (SELECT 
         CASE
             WHEN Age <= 18 THEN 'underage'
             WHEN Age > 18 AND Age <= 35 THEN 'young adults'
             WHEN Age > 35 AND Age <= 55 THEN 'mid-age adults'
             WHEN Age > 55 AND Age <= 100 THEN 'elderly'
             ELSE 'unknown'
         END AS Age_Group,
         Survived
     FROM 
         titanic
    ) AS AgeTable
GROUP BY 
    Age_Group;
```

Result:

![image-20240430115730006](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240430115730006.png)