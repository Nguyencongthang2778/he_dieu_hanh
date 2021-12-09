#include "pintos_thread.h"

struct station {
	int psg_on_board;						//number of passengers have boarded
	int psg_waiting;						//number of passengers are waiting
	int empty_seat;							//number of empty seats
	struct lock *lock;						//lock
	struct condition *all_psg_on_seat;		//All passengers on seat
	struct condition *train_arrived;		//Train arrivied
};

void
station_init(struct station *station_x)
{
	station_x->empty_seat = 0;
	station_x->psg_waiting = 0;
	station_x->psg_on_board = 0;
	//init lock
	station_x->lock = malloc(sizeof(struct lock));
	lock_init(station_x->lock);
	//init condition
	station_x->all_psg_on_seat = malloc(sizeof(struct condition));
	cond_init(station_x->all_psg_on_seat);
	station_x->train_arrived = malloc(sizeof(struct condition));
	cond_init(station_x->train_arrived);
}

void
station_load_train(struct station *station, int count)
{
	lock_acquire(station->lock);
	station->empty_seat = count;
	
	//Wait until all passengers are in their seat
	//Or empty seat = 0
	while ((station->psg_waiting > 0) && (station->empty_seat > 0))
	{
		//when train arrvivied, all threads wakeup
		cond_broadcast(station->train_arrived, station->lock);
		//wait until all passengers sat on seats
		cond_wait(station->all_psg_on_seat, station->lock);
	}

	station->empty_seat = 0;
	lock_release(station->lock);
}

void
station_wait_for_train(struct station *station)
{
	lock_acquire(station->lock);
	station->psg_waiting++;
	while (station->psg_on_board == station->empty_seat || station->empty_seat == 0)
	{
		cond_wait(station->train_arrived, station->lock);
	}
	station->psg_waiting--;
	station->psg_on_board++;
	lock_release(station->lock);
}

void
station_on_board(struct station *station)
{
	//passengers sat on their seat
	lock_acquire(station->lock);
	station->psg_on_board--;
	station->empty_seat--;
	if ((station->empty_seat == 0) || (station->psg_on_board == 0))
	{
		cond_signal(station->all_psg_on_seat, station->lock);
	}

	lock_release(station->lock);
}
