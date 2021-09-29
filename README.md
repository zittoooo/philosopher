# philosopher

## 식사하는 철학자 문제


<img src="https://user-images.githubusercontent.com/18901638/135184452-1937ae50-6e90-4ca8-86e9-c0af19da1f99.png" width="40%">
<!-- ![식사하는철학자]![깃헙-식사하는철학자](https://user-images.githubusercontent.com/18901638/135184452-1937ae50-6e90-4ca8-86e9-c0af19da1f99.png) -->
출처 : wiki 

* 이 프로젝트는 기본적인 프로세스 스레딩, mutex, semaphore, shared memory을 배웁니다.(In this project, you will learn the basics of threading a process and how to work on the same memory space. You will learn how to make threads. You will discover the mutex, semaphore and shared memory.)

### philo_one
1. 철학자는 쓰레드이다.
2. 원탁에 앉아있고, 양 옆에 포크가 있다.

### philo_two
1. 철학자는 쓰레드이다.
2. 원탁에 앉아있고, 테이블 중앙에 포크가 있다.

### philo_three
1. 철학자는 프로세스이다.
2. 원탁에 앉아있고, 테이블 중앙에 포크가 있다.

### 조건
* 철학자는 정해진 시간(time_to_die) 안에 먹지 않으면 죽는다.
* 철학자 한 명이 죽으면 프로그램을 종료한다. (죽는 시간 기준10ms 안에 종료 메세지가 떠야 한다.)
* 철학자는 포크 2개를 집어야 먹을 수 있다.
* 철학자는 먹기 -> 자기 -> 생각하기를 반복한다.
* 프로그램 실행 인자는 총 5개 or 6개이다.
./philo_one  number_of_philosophers  time_to_die  time_to_eat  time_to_sleep  [number_of_times_each_philosopher_must_eat] \
ex) ./philo_one 2 410 200 100 2 으로 실행한다면 \
철학자 수 2명 \
410ms안에 먹어야 철학자 생존 \
200ms동안 먹는다 \
100ms동안 잔다 \
모든 철학자가 2번씩 먹으면 프로그램 종료
