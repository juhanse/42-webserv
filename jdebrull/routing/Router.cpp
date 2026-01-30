/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jdebrull <jdebrull@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:02:26 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/21 13:46:37 by Jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Router.hpp"

Router::Router(const std:vector<Server>& servers) : servers_(servers) {}

RequestContext Router::router(const HTTPRequest& request) {
	RequestContext ctx;
	//todo
	return (ctx);
}