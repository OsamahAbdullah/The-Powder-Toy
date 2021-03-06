/**
 * Powder Toy - HTTP Library (Header)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef HTTP_H
#define HTTP_H

#include <map>
#include <string>

extern std::string userAgent;
void http_init(char *proxy);
void http_done(void);

char *http_simple_get(const char *uri, int *ret, int *len);
char *http_auth_get(const char *uri, const char *user, const char *pass, const char * session_id, int *ret, int *len);
char *http_simple_post(const char *uri, const char *data, int dlen, int *ret, int *len);

void http_auth_headers(void *ctx, const char *user, const char *pass, const char * session_id);

void *http_async_req_start(void *ctx, const char *uri, const char *data, int dlen, int keep);
void http_async_add_header(void *ctx, const char *name, const char *data);
int http_async_req_status(void *ctx);
void http_async_get_length(void *ctx, int *total, int *done);
char *http_async_req_stop(void *ctx, int *ret, int *len);
void http_force_close(void *ctx);
void http_async_req_close(void *ctx);

std::string FindBoundary(std::map<std::string, std::string>, std::string boundary);
std::string GetMultipartMessage(std::map<std::string, std::string>, std::string boundary);
void http_add_multipart_header(void *ctx, std::string boundary);
char *http_multipart_post(const char *uri, const char *const *names, const char *const *parts, size_t *plens, const char *user, const char *pass, const char * session_id, int *ret, int *len);

const char *http_ret_text(int ret);

#endif
