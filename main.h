/* context.c */
BOOLEAN find_member_symbol(TOKEN *symbol, DECL_MEMBER *decl_ptr, DECL_ID **decl_id);
BOOLEAN find_list_symbol(TOKEN *symbol, DECL_MEMBER *decl_ptr, DECL_MEMBER **decl_found, DECL_ID **decl_id);
BOOLEAN find_symbol(TOKEN *symbol, DECL_MEMBER **decl_found, DECL_ID **decl_id);
void add_to_context(DECL_MEMBER *decl);
void add_decl_to_context(DECL *decl);
void new_context(int type, TOKEN *name);
void pop_context(void);
void init_context(void);

/* control.c */
void parse_control(void);

/* convert.c */
int parse_statement(TOKEN *first_token);
int parse_new_statement(void);
void parse_file(void);

/* declare.c */
void find_right_paren(void);
void element_copy(DECL_MEMBER *src, DECL_MEMBER *dest);
int get_var_list(DECL_ID **list_ptr, TOKEN *sep_token);
void parse_structure(DECL_MEMBER **list_ptr);
int parse_type(DECL_MEMBER *el_ptr, TOKEN *token);
int get_element(DECL_MEMBER **element, TOKEN *token);
void get_decl_list(DECL *decl);
void parse_declare(TOKEN *first_token);

/* decl_out.c */
void out_pointer(TOKEN *name, BOOLEAN use_parens);
void out_bound(TOKEN *bound);
void out_decl_type(DECL_MEMBER *decl_ptr);
void out_struct(DECL_MEMBER *el_ptr);
void out_decl_member(DECL_MEMBER *decl_list, TOKEN *decl_token);
void out_decl(DECL *decl);

/* error.c */
void parse_mesg(char *error_string, char *error_type, char error_eol);
void parse_error(char *error_string);
void control_error(char *error_string);
void parse_warning(char *warning_string);

/* io.c */
void out_data(char *string, int length);
void out_white_space(TOKEN *token);
void out_must_white(TOKEN *token);
void out_pre_line(TOKEN *token);
void out_pre_white(TOKEN *token);
void out_token_name(TOKEN *token);
void out_token(TOKEN *token);
void out_must_token(TOKEN *token);
void out_cvt_name(TOKEN *token);
void out_str(char *string);
void out_char(char ch);
void out_to_start(void);
void out_type(int type);
void out_init(void);
void out_str_const(char *str_ptr, int len);
void cvt_octal(TOKEN *token, char octal_string[]);

/* main.c */
void get_at_decl(void);
void cvt_file(char *file_name);
void main(int argc, char *argv[]);

/* mem.c */
char *get_mem(unsigned int size);
void get_context_ptr(CONTEXT **context);
void get_token_ptr(TOKEN **token);
void get_var_ptr(DECL_ID **var);
void free_var_list(DECL_ID *list_ptr);
void get_element_ptr(DECL_MEMBER **element);
void free_decl_list(DECL_MEMBER *element);
void get_param_ptr(PARAM_LIST **param);
void free_param_list(PARAM_LIST *param_list);
void get_decl_ptr(DECL **decl);
void free_decl(DECL *decl_list);

/* parse.c */
void get_param_list(PARAM_LIST **param_head);
void parse_param_list(PARAM_LIST *param_list, DECL **decl_list, DECL **extra_decl_list);
void parse_till(int type, TOKEN *token);
void parse_till_end(TOKEN *token);
void parse_to_end(void);
void check_eol(void);
int parse_simple_variable(TOKEN *token, TOKEN *next_token);
void out_ident(TOKEN *ident, DECL_MEMBER *decl, DECL_ID *decl_id);
int parse_member(TOKEN *token, DECL_MEMBER *decl, DECL_ID *decl_id);
int parse_variable(TOKEN *token, DECL_MEMBER **var_decl, DECL_ID **var_decl_id);
BOOLEAN check_cvt_id(TOKEN *token, CVT_ID *cvt_id, char **cvt_string);
int parse_function(TOKEN *token);
int parse_expression(TOKEN *token);
void parse_do(TOKEN *first_token);
void parse_end(TOKEN *first_token);
void parse_if(TOKEN *first_token);
void parse_then(void);
void parse_else(TOKEN *first_token);
void parse_goto(TOKEN *first_token);
void parse_go(TOKEN *first_token);
void parse_call(TOKEN *first_token);
void parse_return(TOKEN *first_token);
void parse_identifier(TOKEN *first_token);
void parse_label(void);
void parse_eol(TOKEN *first_token);
void parse_int_ctl(TOKEN *first_token);
void parse_outport(void);
void parse_output(TOKEN *first_token);
void parse_outword(TOKEN *first_token);
void parse_outhword(TOKEN *first_token);

/* token.c */
int get_token(TOKEN *token);
void token_copy(TOKEN *src, TOKEN *dest);

