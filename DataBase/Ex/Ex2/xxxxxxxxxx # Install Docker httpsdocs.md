# 实例的租用

配置：腾讯云，香港地区，竞价实例，SA5标准型4核8GB，Ubuntu20.04

# 镜像的创建

## 安装docker并且运行hello-world验证

```bash
sudo apt-get update
sudo apt-get install ca-certificates curl gnupg
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
apt list -a docker-ce
sudo apt-get install docker-ce=5:19.03.10~3-0~ubuntu-focal
sudo docker run hello-world
```



![image-20240409102554097](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240409102554097.png)

## 换源（Aliyun）

![image-20240409103025025](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240409103025025.png)

## 查看kubernetes的版本并且下载1.18版本使用kubeam version验证安装是否成功

![image-20240409103149180](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240409103149180.png)

## 关闭交换和删除known_hosts文件

![image-20240409103231695](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240409103231695.png)

```bash
# Install Docker https://docs.docker.com/engine/install/ubuntu/
# Add Docker's official GPG key:
sudo apt-get update
sudo apt-get install ca-certificates curl gnupg
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

sudo apt-get update

# Install docker via apt-get and run hello-world example
# sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
apt list -a docker-ce
sudo apt-get install docker-ce=5:19.03.10~3-0~ubuntu-focal
sudo docker run hello-world


# Install three components of Kubernetes 1.18
# Change the Aliyun source for Kubernetes https://blog.csdn.net/qq_40907977/article/details/110951076
sudo apt-get install apt-transport-https
curl https://mirrors.aliyun.com/kubernetes/apt/doc/apt-key.gpg | sudo apt-key add - 
sudo vim /etc/apt/sources.list.d/kubernetes.list
# add content: deb https://mirrors.aliyun.com/kubernetes/apt/ kubernetes-xenial main
sudo apt-get update
apt-cache madison kubeadm
sudo apt-get install -y kubelet=1.18.0-00 kubeadm=1.18.0-00 kubectl=1.18.0-00
kubeadm version

# Launch the master node
sudo swapoff -a
sudo kubeadm init --apiserver-advertise-address=172.19.16.8 --image-repository registry.aliyuncs.com/google_containers --service-cidr=10.96.0.0/12  --pod-network-cidr=10.244.0.0/16

# Set kubectl in master node
mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config

# Set flannel in master node
kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml

# Scale the application
kubectl scale deployment frontend --replicas=5
```

![image-20240402102714983](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240402102714983.png)

```bash
kubeadm join 172.19.0.14:6443 --token gc92e7.mhcy04py9yamyu04 \
    --discovery-token-ca-cert-hash sha256:4fef2226583d439cdce103242769c4ecc860a6733556a0e39c31f9d202620d5c
```

```bash
mkdir -p $HOME/.kube
  sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
  sudo chown $(id -u):$(id -g) $HOME/.kube/config
```

![image-20240402103131431](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240402103131431.png)

```bash
kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
kubectl get nodes
```

![image-20240402104019410](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240402104019410.png)

```bash
kubectl apply -f redis-leader-deployment.yaml
```

![image-20240402104817555](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240402104817555.png)

![image-20240402110328158](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240402110328158.png)

![image-20240402110431896](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240402110431896.png)

![image-20240402110526982](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240402110526982.png)

![image-20240402111304190](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240402111304190.png)

![image-20240402112929138](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240402112929138.png)

![image-20240402113620973](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240402113620973.png)

![image-20240402114047119](/Users/wangshibo/Library/Application Support/typora-user-images/image-20240402114047119.png)