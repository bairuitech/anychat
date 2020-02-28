#if !defined(WIN32)
#	include <sys/time.h>
#	include <time.h>
#endif

#include "acthread.h"

#ifdef WIN32

int ac_thread_mutex_init( ac_thread_mutex_t * mutex, void * attr )
{
	::InitializeCriticalSection(mutex);
	return 0;
}

int ac_thread_mutex_destroy( ac_thread_mutex_t * mutex )
{
	::DeleteCriticalSection(mutex);
	return 0;
}

int ac_thread_mutex_lock( ac_thread_mutex_t * mutex )
{
	::EnterCriticalSection(mutex);
	return 0;
}

int ac_thread_mutex_unlock( ac_thread_mutex_t * mutex )
{
	::LeaveCriticalSection(mutex);
	return 0;
}

int ac_thread_cond_init( ac_thread_cond_t * cond, void * attr )
{
	*cond = CreateEvent( NULL, FALSE, FALSE, NULL );
	return NULL == *cond ? GetLastError() : 0;
}

int ac_thread_cond_destroy( ac_thread_cond_t * cond )
{
	int ret = CloseHandle( *cond );
	return 0 == ret ? GetLastError() : 0;
}

/*
Caller MUST be holding the mutex lock; the
lock is released and the caller is blocked waiting
on 'cond'. When 'cond' is signaled, the mutex
is re-acquired before returning to the caller.
*/
int ac_thread_cond_wait( ac_thread_cond_t * cond, ac_thread_mutex_t * mutex )
{
	int ret = 0;
	ac_thread_mutex_unlock( mutex );
	ret = WaitForSingleObject( *cond, INFINITE );
	ac_thread_mutex_lock( mutex );
	return ret;
}

int ac_thread_cond_signal( ac_thread_cond_t * cond )
{
	int ret = SetEvent( *cond );
	return 0 == ret ? GetLastError() : 0;
}

ac_thread_t ac_thread_self()
{
	return (ac_thread_t)GetCurrentThreadId();
}

int ac_thread_attr_init( ac_thread_attr_t * attr )
{
	memset( attr, 0, sizeof( ac_thread_attr_t ) );
	return 0;
}

int ac_thread_attr_destroy( ac_thread_attr_t * attr )
{
	return 0;
}

int ac_thread_attr_setdetachstate( ac_thread_attr_t * attr, int detachstate )
{
	attr->detachstate = detachstate;
	return 0;
}

int ac_thread_attr_setstacksize( ac_thread_attr_t * attr, size_t stacksize )
{
	attr->stacksize = (int)stacksize;
	return 0;
}

int ac_thread_create( ac_thread_t * thread, ac_thread_attr_t * attr,
		ac_thread_func_t myfunc, void * args )
{
	HANDLE h = 0;
#if defined(WINCE)
	DWORD dwId;
	h = CreateThread(NULL, attr?attr->stacksize:0, myfunc, args, attr->stacksize ? STACK_SIZE_PARAM_IS_A_RESERVATION : 0, &dwId);
#else
    unsigned tid;
	if( NULL != attr ) {
		h = (HANDLE)_beginthreadex( NULL, attr->stacksize, myfunc, args, 0, &tid );
	} else {
		h = (HANDLE)_beginthreadex( NULL, 0, myfunc, args, 0, &tid );		// _beginthreadex returns 0 on an error
	}
#endif
	if(h > 0)
		*thread = h;
	return h > 0 ? 0 : GetLastError();
}

int ac_thread_join(ac_thread_t thread, void ** args)
{
    WaitForSingleObject(thread,INFINITE);
    CloseHandle(thread);
	return 0;
}

#endif



int ac_thread_cond_timedwait( ac_thread_cond_t * cond, ac_thread_mutex_t * mutex, int millionsecond )
{
    int ret = 0;
#ifdef WIN32
	ac_thread_mutex_unlock( mutex );
	ret = WaitForSingleObject( *cond, millionsecond );
	ac_thread_mutex_lock( mutex );
#else
	struct timespec abstime;
	struct timeval now;
	gettimeofday(&now, NULL);
	int nsec = now.tv_usec * 1000 + (millionsecond % 1000) * 1000000;
	abstime.tv_nsec = nsec % 1000000000;
	abstime.tv_sec = now.tv_sec + nsec / 1000000000 + millionsecond / 1000;
    ret = pthread_cond_timedwait(cond, mutex,&abstime);
#endif
    return ret;
}
