
#ifndef __ANYCHAT_THREAD_INCLUDE_H___
#define __ANYCHAT_THREAD_INCLUDE_H___

#if !defined(WIN32) && !defined(WINCE)

/// pthread

#include <pthread.h>
#include <unistd.h>

typedef void * ac_thread_result_t;
typedef pthread_mutex_t ac_thread_mutex_t;
typedef pthread_cond_t  ac_thread_cond_t;
typedef pthread_t       ac_thread_t;
typedef pthread_attr_t  ac_thread_attr_t;

#define ac_thread_mutex_init     pthread_mutex_init
#define ac_thread_mutex_destroy  pthread_mutex_destroy
#define ac_thread_mutex_lock     pthread_mutex_lock
#define ac_thread_mutex_unlock   pthread_mutex_unlock

#define ac_thread_cond_init      pthread_cond_init
#define ac_thread_cond_destroy   pthread_cond_destroy
#define ac_thread_cond_wait      pthread_cond_wait
#define ac_thread_cond_signal    pthread_cond_signal

#define ac_thread_attr_init           pthread_attr_init
#define ac_thread_attr_destroy        pthread_attr_destroy
#define ac_thread_attr_setdetachstate pthread_attr_setdetachstate
#define AC_THREAD_CREATE_DETACHED     PTHREAD_CREATE_DETACHED
#define ac_thread_attr_setstacksize   pthread_attr_setstacksize

#define ac_thread_self    pthread_self
#define ac_thread_create  pthread_create
#define ac_thread_join    pthread_join

#define ac_thread_CALL
typedef ac_thread_result_t ( * ac_thread_func_t )( void * args );

#ifndef sp_sleep
#define sp_sleep(x) sleep(x)
#endif

#elif defined(WIN32) || defined(WINCE)

// win32 thread

#include <windows.h>

#if !defined(WINCE)
#include <process.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef HANDLE ac_thread_t;

#if defined(WINCE)
typedef DWORD ac_thread_result_t;
#define ac_thread_CALL WINAPI
#else
typedef unsigned ac_thread_result_t;
#define ac_thread_CALL __stdcall
#endif

typedef ac_thread_result_t ( __stdcall * ac_thread_func_t )( void * args );

typedef CRITICAL_SECTION  ac_thread_mutex_t;
typedef HANDLE  ac_thread_cond_t;

//typedef DWORD   ac_thread_attr_t;
typedef struct tagac_thread_attr {
	int stacksize;
	int detachstate;
} ac_thread_attr_t;

#define AC_THREAD_CREATE_DETACHED 1

#ifndef ac_sleep
#define ac_sleep(x) Sleep(1000*x)
#endif

int ac_thread_mutex_init( ac_thread_mutex_t * mutex, void * attr );
int ac_thread_mutex_destroy( ac_thread_mutex_t * mutex );
int ac_thread_mutex_lock( ac_thread_mutex_t * mutex );
int ac_thread_mutex_unlock( ac_thread_mutex_t * mutex );

int ac_thread_cond_init( ac_thread_cond_t * cond, void * attr );
int ac_thread_cond_destroy( ac_thread_cond_t * cond );
int ac_thread_cond_wait( ac_thread_cond_t * cond, ac_thread_mutex_t * mutex );
int ac_thread_cond_signal( ac_thread_cond_t * cond );

int ac_thread_attr_init( ac_thread_attr_t * attr );
int ac_thread_attr_destroy( ac_thread_attr_t * attr );
int ac_thread_attr_setdetachstate( ac_thread_attr_t * attr, int detachstate );
int ac_thread_attr_setstacksize( ac_thread_attr_t * attr, size_t stacksize );

int ac_thread_create( ac_thread_t * thread, ac_thread_attr_t * attr,
		ac_thread_func_t myfunc, void * args );
int ac_thread_join(ac_thread_t thread, void ** args =NULL);
ac_thread_t ac_thread_self();

#ifdef __cplusplus
}
#endif



#endif


int ac_thread_cond_timedwait( ac_thread_cond_t * cond, ac_thread_mutex_t * mutex, int millionsecond );


// 自动加锁，避免加锁区域异常之后不能解锁
class CAnyChatAutoLock
{
public:
	explicit CAnyChatAutoLock(ac_thread_mutex_t& m) : mutex(m)
	{
		ac_thread_mutex_lock(&mutex);
	}
	~CAnyChatAutoLock()
	{
		ac_thread_mutex_unlock(&mutex);
	}

private:
	ac_thread_mutex_t&	mutex;
};


#endif	//__ANYCHAT_THREAD_INCLUDE_H___

