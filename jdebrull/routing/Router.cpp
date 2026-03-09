#include "Router.hpp"

Router::Router(const std:vector<Server>& servers) : servers_(servers) {}

RequestContext Router::router(const HTTPRequest& request) {
	RequestContext ctx;
	//todo
	return (ctx);
}