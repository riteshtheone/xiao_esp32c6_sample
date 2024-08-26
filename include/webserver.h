#ifndef __WEBSERVER_H_
#define __WEBSERVER_H_

#include <ESPAsyncWebServer.h>

class WebServer;

class WebServer {
   private:
    AsyncWebServer _server;
   public:
    WebServer(uint16_t port);
    ~WebServer();

    void begin();
    void headers();
    void routes();
};

#endif /* __WEBSERVER_H_ */
