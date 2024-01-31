#include<bits/stdc++.h>
using namespace std;


void accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx) {
    cout << "Accepted connection" << endl;
}

void accept_error_cb(struct evconnlistener *listener, void *ctx) {
    struct event_base *base = evconnlistener_get_base(listener);
    int err = EVUTIL_SOCKET_ERROR();
    cerr << "Error " << err << " (" << evutil_socket_error_to_string(err) << ") on the listener. Shutting down." <<endl;
    event_base_loopexit(base, NULL);
}

int main() {
    struct event_base *base;
    struct evconnlistener *listener;
    struct sockaddr_in sin;

    base = event_base_new();
    if (!base) {
        cerr << "Could not initialize libevent!" <<endl;
        return 1;
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(12345); 

    listener = evconnlistener_new_bind(base, accept_conn_cb, NULL, LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, -1, (struct sockaddr*)&sin, sizeof(sin));
    if (!listener) {
        cerr << "Could not create a listener!" <<endl;
        return 1;
    }
    evconnlistener_set_error_cb(listener, accept_error_cb);

    event_base_dispatch(base);

    evconnlistener_free(listener);
    event_base_free(base);

    return 0;
}
