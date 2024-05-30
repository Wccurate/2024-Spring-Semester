# 安装Java JDK开发 JRE 运行环境

```bash
# Install JAVA and Setup environment path
sudo apt-get install openjdk-8-jre openjdk-8-jdk
vim ~/.bashrc
# export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
source ~/.bashrc
```

## java安装完成

![image-20240423101757142](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240423101757142.png)

# 上传和解压hadoop和spark压缩包

```bash
scp {hadoop-2.7.0.tar.gz,spark-2.1.0-bin-with-hive.tgz} ubuntu@118.195.129.227:/home/ubuntu/
```

![image-20240423102236729](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240423102236729.png)

![image-20240423103447166](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240423103447166.png)

# 设置Hadoop集群

```bash
wget https://archive.apache.org/dist/hadoop/common/hadoop-2.7.0/hadoop-2.7.0.tar.gz
sudo tar -zxf hadoop-2.7.0.tar.gz -C /usr/local
sudo chown -R ubuntu:root ./hadoop
bin/hdfs namenode -format
sbin/start-all.sh
bin/hdfs dfs -mkdir -p /user/ubuntu
```

![image-20240423103744607](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240423103744607.png)

![image-20240423104052128](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240423104052128.png)

```bash
# Setup Spark with Hive over Hadoop Cluster
sudo tar -zxf spark-2.1.0-bin-h27hive.tgz  -C /usr/local
sudo chown -R hadoop:hadoop ./sparkwithhive
cp ./conf/spark-env.sh.template ./conf/spark-env.sh
vim ./conf/spark-env.sh
# export SPARK_DIST_CLASSPATH=$(/usr/local/hadoop/bin/hadoop classpath)
```



![image-20240423111249855](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240423111249855.png)

# 使用已有镜像创建三个实例并且配置hostname和hosts

![image-20240423112851408](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240423112851408.png)

## 格式化

![image-20240423113149535](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240423113149535.png)

![image-20240423113414706](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240423113414706.png)

![image-20240423114213472](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240423114213472.png)