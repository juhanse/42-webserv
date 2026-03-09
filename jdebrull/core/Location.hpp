#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <string>
# include <set>
# include <map>
# include <vector>
# include <iostream>

class LocationConfig
{
	private:
		size_t			client_max_size;
		std::string		path;
		std::string		root;
		std::string		upload;
		std::string		return_url;
		int				return_code;
		bool			autoindex;

		std::vector<std::string>			index;
		std::set<std::string>				methods;
		std::map<std::string, std::string>	cgi_extension;

	public:
		LocationConfig();
		~LocationConfig();
		
		const std::string&							getPath() const;
		const std::string&							getRoot() const;
		const std::vector<std::string>&				getIndex() const;
		const std::set<std::string>&				getMethods() const;
		size_t										getClientMaxBodySize() const;
		bool										getAutoIndex() const;
		int											getReturnCode() const;
		const std::string&							getReturnUrl() const;
		const std::map<std::string, std::string>&	getCgiExtensions() const;
		const std::string&							getUploadPath() const;

		void	setPath(const std::string& p);
		void	setRoot(const std::string& r);
		void	setClientMaxBodySize(size_t size);
		void	setAutoIndex(bool value);
		void	setReturn(int code, const std::string& url);
		void	setUpload(const std::string& path);

		void	addIndex(const std::string& file);
		void	addMethod(const std::string& method);
		void	addCgiExtension(const std::string& ext, const std::string& path);

};

#endif