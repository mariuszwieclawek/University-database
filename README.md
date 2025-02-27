# University-database

# Docker
sudo service docker start
sudo docker build -t university_database .
sudo docker run -it --name uni-db-container university_database

sudo docker start -i uni-db-container


sudo docker stop uni-db-container
sudo docker rm uni-db-container


