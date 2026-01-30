CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

TARGET		= webserv

SRCS		=	main.cpp config/ConfigParser.cpp config/ParseListen.cpp config/ParseServerName.cpp \
				config/ParseRoot.cpp config/ParseIndex.cpp config/ParseBodySize.cpp config/ParseErrorPage.cpp \
				utils/utils.cpp \

OBJDIR		= obj
OBJS		= $(SRCS:%.cpp=$(OBJDIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(OBJDIR)/%.o: %.cpp 
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re