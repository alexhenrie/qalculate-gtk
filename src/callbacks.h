/*
    Qalculate (GTK+ UI)

    Copyright (C) 2003-2007, 2008, 2016  Hanna Knutsson (hanna.knutsson@protonmail.com)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
*/

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>

#define EXPAND_TO_ITER(model, view, iter)		GtkTreePath *path = gtk_tree_model_get_path(model, &iter); \
							gtk_tree_view_expand_to_path(GTK_TREE_VIEW(view), path); \
							gtk_tree_path_free(path);
#define SCROLL_TO_ITER(model, view, iter)		GtkTreePath *path2 = gtk_tree_model_get_path(model, &iter); \
							gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(view), path2, NULL, FALSE, 0, 0); \
							gtk_tree_path_free(path2);							
#define EXPAND_ITER(model, view, iter)			GtkTreePath *path = gtk_tree_model_get_path(model, &iter); \
							gtk_tree_view_expand_row(GTK_TREE_VIEW(view), path, FALSE); \
							gtk_tree_path_free(path);							

#include "main.h"

struct mode_struct {
	PrintOptions po;
	EvaluationOptions eo;
	AssumptionType at;
	AssumptionSign as;
	int precision;
	string name;
	bool rpn_mode;
	bool interval;
	bool adaptive_interval_display;
	bool variable_units_enabled;
};

enum {
	QALCULATE_HISTORY_EXPRESSION,
	QALCULATE_HISTORY_TRANSFORMATION,
	QALCULATE_HISTORY_RESULT,
	QALCULATE_HISTORY_RESULT_APPROXIMATE,
	QALCULATE_HISTORY_PARSE_WITHEQUALS,
	QALCULATE_HISTORY_PARSE,
	QALCULATE_HISTORY_PARSE_APPROXIMATE,
	QALCULATE_HISTORY_WARNING,
	QALCULATE_HISTORY_ERROR,
	QALCULATE_HISTORY_OLD,
	QALCULATE_HISTORY_REGISTER_MOVED,
	QALCULATE_HISTORY_RPN_OPERATION
};

DECLARE_BUILTIN_FUNCTION(AnswerFunction)
DECLARE_BUILTIN_FUNCTION(ExpressionFunction)

class ViewThread : public Thread {
protected:
	virtual void run();
};

class CommandThread : public Thread {
protected:
	virtual void run();
};

class FetchExchangeRatesThread : public Thread {
protected:
	virtual void run();
};


bool can_display_unicode_string_function(const char *str, void *w);
bool can_display_unicode_string_function_exact(const char *str, void *w);
void set_unicode_buttons();
void set_operator_symbols();

cairo_surface_t *draw_structure(MathStructure &m, PrintOptions po = default_print_options, InternalPrintStruct ips = top_ips, gint *point_central = NULL, int scaledown = 0, GdkRGBA *color = NULL);

void update_status_text();

void set_result_size_request();
void set_expression_size_request();

void create_umenu(void);
void create_umenu2(void);
void create_vmenu(void);
void create_fmenu(void);
void create_pmenu(GtkWidget *item);
void create_pmenu2(void);

void update_vmenu();
void update_fmenu();
void update_umenu();

void update_completion();

void generate_functions_tree_struct();
void generate_variables_tree_struct();
void generate_units_tree_struct();

gboolean on_display_errors_timeout(gpointer data);
gboolean on_check_version_idle(gpointer data);

void update_functions_tree();
void update_variables_tree();
void update_units_tree();
void update_unit_selector_tree();
void update_datasets_tree();
void on_tFunctions_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);
void on_tFunctionCategories_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);
void on_tVariables_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);
void on_tVariableCategories_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);
void on_tUnits_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);
void on_tUnitCategories_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);
void on_tDataObjects_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);
void on_tDatasets_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);
void on_tDataProperties_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);
void on_tUnitSelector_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);
void on_tUnitSelectorCategories_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);

void execute_expression(bool force = true, bool do_mathoperation = false, MathOperation op = OPERATION_ADD, MathFunction *f = NULL, bool do_stack = false, size_t stack_index = 0, string execute_str = string(), string str = string(), bool check_exrates = true);
void setResult(Prefix *prefix = NULL, bool update_history = true, bool update_parse = false, bool force = false, string transformation = "", size_t stack_index = 0, bool register_moved = false);

void set_rpn_mode(bool b);
void calculateRPN(int op);
void calculateRPN(MathFunction *f);
void RPNRegisterAdded(string text, gint index = 0);
void RPNRegisterRemoved(gint index);
void RPNRegisterChanged(string text, gint index);

void result_display_updated();
void result_format_updated();
void result_action_executed();
void result_prefix_changed(Prefix *prefix = NULL);
void expression_calculation_updated();
void expression_format_updated(bool recalculate = false);


void insert_text(const gchar *name);

void recreate_recent_functions();
void recreate_recent_variables();
void recreate_recent_units();
void function_inserted(MathFunction *object);
void variable_inserted(Variable *object);
void unit_inserted(Unit *object);

void on_tPlotFunctions_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);

void on_tSubfunctions_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);
void on_tFunctionArguments_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);
void update_function_arguments_list(MathFunction *f);

void on_tNames_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);

void convert_in_wUnits(int toFrom = -1);

void convert_to_unit(GtkMenuItem *w, gpointer user_data);

void save_defs();
void save_mode();

void load_preferences();
void save_preferences(bool mode = false);
void edit_preferences();

gint completion_sort_func(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data);
gint string_sort_func(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data);
gint int_string_sort_func(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data);

void set_prefix(GtkMenuItem *w, gpointer user_data);

void manage_variables();
void manage_functions();
void manage_units();

void set_clean_mode(GtkMenuItem *w, gpointer user_data);
void set_functions_enabled(GtkMenuItem *w, gpointer user_data);
void set_variables_enabled(GtkMenuItem *w, gpointer user_data);
void set_donot_calcvars(GtkMenuItem *w, gpointer user_data);
void set_unknownvariables_enabled(GtkMenuItem *w, gpointer user_data);
void set_units_enabled(GtkMenuItem *w, gpointer user_data);
void apply_function(GtkMenuItem *w, gpointer user_data);
void insert_function(GtkMenuItem *w, gpointer user_data);
void insert_variable(GtkMenuItem *w, gpointer user_data);
void insert_prefix(GtkMenuItem *w, gpointer user_data);
void insert_unit(GtkMenuItem *w, gpointer user_data);

void insert_button_function(GtkMenuItem *w, gpointer user_data);
void insert_button_function_norpn(GtkMenuItem *w, gpointer user_data);
void insert_button_variable(GtkWidget *w, gpointer user_data);
void insert_button_unit(GtkMenuItem *w, gpointer user_data);
void insert_button_currency(GtkMenuItem *w, gpointer user_data);

void new_function(GtkMenuItem *w, gpointer user_data);
void new_unknown(GtkMenuItem *w, gpointer user_data);
void new_variable(GtkMenuItem *w, gpointer user_data);
void new_matrix(GtkMenuItem *w, gpointer user_data);
void new_vector(GtkMenuItem *w, gpointer user_data);
void new_unit(GtkMenuItem *w, gpointer user_data);
void add_as_variable();

void fetch_exchange_rates(int timeout);

bool edit_argument(Argument *arg = NULL);

void edit_unknown(const char *category = "", Variable *v = NULL, GtkWidget *win = NULL);
void edit_variable(const char *category = "", Variable *v = NULL, MathStructure *mstruct_ = NULL, GtkWidget *win = NULL);
void edit_matrix(const char *category = "", Variable *v = NULL, MathStructure *mstruct_ = NULL, GtkWidget *win = NULL, gboolean create_vector = FALSE);
void insert_matrix(const MathStructure *initial_value = NULL, GtkWidget *win = NULL, gboolean create_vector = FALSE, bool is_text_struct = false, bool is_result = false);
void import_csv_file(GtkWidget *win = NULL);
void export_csv_file(KnownVariable *v = NULL, GtkWidget *win = NULL);

void edit_dataobject(DataSet *ds, DataObject *o = NULL, GtkWidget *win = NULL);
void edit_dataset(DataSet *ds = NULL, GtkWidget *win = NULL);

void edit_names(ExpressionItem *item = NULL, const gchar *namestr = NULL, GtkWidget *win = NULL, bool is_dp = false, DataProperty *dp = NULL);

gchar *font_name_to_css(const char *font_name);

#ifdef __cplusplus
extern "C" {
#endif

void on_completion_match_selected(GtkTreeView*, GtkTreePath *path, GtkTreeViewColumn*, gpointer);
void on_units_convert_view_row_activated(GtkTreeView*, GtkTreePath *path, GtkTreeViewColumn*, gpointer);
void units_convert_resize_popup();

void *view_proc(void*);
void *command_proc(void*);
void on_message_bar_response(GtkInfoBar *w, gint response_id, gpointer);
void on_expressiontext_populate_popup(GtkTextView *w, GtkMenu *menu, gpointer user_data);
void on_combobox_base_changed(GtkComboBox *w, gpointer user_data);
void on_combobox_numerical_display_changed(GtkComboBox *w, gpointer user_data);
void on_combobox_fraction_mode_changed(GtkComboBox *w, gpointer user_data);
void on_combobox_approximation_changed(GtkComboBox *w, gpointer user_data);
void on_expander_keypad_expanded(GObject *o, GParamSpec *param_spec, gpointer user_data);
void on_expander_history_expanded(GObject *o, GParamSpec *param_spec, gpointer user_data);
void on_expander_stack_expanded(GObject *o, GParamSpec *param_spec, gpointer user_data);
void on_expander_convert_expanded(GObject *o, GParamSpec *param_spec, gpointer user_data);
void on_menu_item_meta_mode_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_meta_mode_save_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_meta_mode_delete_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_quit_activate(GtkMenuItem *w, gpointer user_data);
void on_colorbutton_status_error_color_color_set(GtkColorButton *w, gpointer user_data);
void on_colorbutton_status_warning_color_color_set(GtkColorButton *w, gpointer user_data);
void on_preferences_checkbutton_copy_separator_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_lower_case_numbers_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_e_notation_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_lower_case_e_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_alternative_base_prefixes_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_spell_out_logical_operators_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_unicode_signs_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_display_expression_status_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_enable_completion_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_fetch_exchange_rates_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_save_defs_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_save_mode_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_rpn_keys_only_toggled(GtkToggleButton *w, gpointer);
void on_preferences_checkbutton_dot_as_separator_toggled(GtkToggleButton *w, gpointer);
void on_preferences_checkbutton_load_defs_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_custom_result_font_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_custom_expression_font_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_checkbutton_custom_status_font_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_radiobutton_dot_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_radiobutton_ex_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_radiobutton_asterisk_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_radiobutton_slash_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_radiobutton_division_slash_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_radiobutton_division_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_radiobutton_digit_grouping_none_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_radiobutton_digit_grouping_standard_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_radiobutton_digit_grouping_locale_toggled(GtkToggleButton *w, gpointer user_data);
void on_preferences_button_result_font_toggled(GtkButton *w, gpointer user_data);
void on_preferences_button_expression_font_toggled(GtkButton *w, gpointer user_data);
void on_preferences_button_status_font_toggled(GtkButton *w, gpointer user_data);
void on_units_togglebutton_from_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_units_button_convert_clicked(GtkButton *button, gpointer user_data);
void on_units_togglebutton_to_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_units_entry_from_val_activate(GtkEntry *entry, gpointer user_data);
void on_units_entry_to_val_activate(GtkEntry *entry, gpointer user_data);
gboolean on_units_entry_from_val_focus_out_event(GtkEntry *entry, GdkEventFocus *event, gpointer user_data);
gboolean on_units_entry_to_val_focus_out_event(GtkEntry *entry, GdkEventFocus *event, gpointer user_data);
void on_units_button_close_clicked(GtkButton *button, gpointer user_data);
void on_radiobutton_radians_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_radiobutton_degrees_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_radiobutton_gradians_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_radiobutton_no_default_angle_unit_toggled(GtkToggleButton *togglebutton, gpointer user_data);
gboolean on_gcalc_exit(GtkWidget *widget, GdkEvent *event, gpointer user_data);
void on_expression_activate(GtkEntry *entry, gpointer user_data);
void on_button_execute_clicked(GtkButton *button, gpointer user_data);
void on_button_del_clicked(GtkButton *w, gpointer user_data);
void on_button_ac_clicked(GtkButton *w, gpointer user_data);
void on_button_hyp_toggled(GtkToggleButton *w, gpointer user_data);
void on_button_inv_toggled(GtkToggleButton *w, gpointer user_data);
void on_button_fraction_toggled(GtkToggleButton *w, gpointer user_data);
void on_button_tan_clicked(GtkButton *w, gpointer user_data);
void on_button_sine_clicked(GtkButton *w, gpointer user_data);
void on_button_cosine_clicked(GtkButton *w, gpointer user_data);
void on_button_store_clicked(GtkButton *w, gpointer user_data);
void on_button_mod_clicked(GtkButton *w, gpointer user_data);
void on_button_reciprocal_clicked(GtkButton *w, gpointer user_data);
void on_togglebutton_expression_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_togglebutton_result_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_expression_changed(GtkEditable *w, gpointer user_data);
void on_expression_move_cursor(GtkEntry*, GtkMovementStep, gint, gboolean, gpointer);
void on_button_zero_clicked(GtkButton *w, gpointer user_data);
void on_button_one_clicked(GtkButton *w, gpointer user_data);
void on_button_two_clicked(GtkButton *w, gpointer user_data);
void on_button_three_clicked(GtkButton *w, gpointer user_data);
void on_button_four_clicked(GtkButton *w, gpointer user_data);
void on_button_five_clicked(GtkButton *w, gpointer user_data);
void on_button_six_clicked(GtkButton *w, gpointer user_data);
void on_button_seven_clicked(GtkButton *w, gpointer user_data);
void on_button_eight_clicked(GtkButton *w, gpointer user_data);
void on_button_nine_clicked(GtkButton *w, gpointer user_data);
void on_button_dot_clicked(GtkButton *w, gpointer user_data);
void on_button_brace_open_clicked(GtkButton *w, gpointer user_data);
void on_button_brace_close_clicked(GtkButton *w, gpointer user_data);
void on_button_times_clicked(GtkButton *w, gpointer user_data);
void on_button_add_clicked(GtkButton *w, gpointer user_data);
void on_button_sub_clicked(GtkButton *w, gpointer user_data);
void on_button_divide_clicked(GtkButton *w, gpointer user_data);
void on_button_ans_clicked(GtkButton *w, gpointer user_data);
void on_button_exp_clicked(GtkButton *w, gpointer user_data);
void on_button_xy_clicked(GtkButton *w, gpointer user_data);
void on_button_square_clicked();
void on_button_sqrt_clicked(GtkButton *w, gpointer user_data);
void on_button_log_clicked(GtkButton *w, gpointer user_data);
void on_button_ln_clicked(GtkButton *w, gpointer user_data);
void on_menu_item_manage_variables_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_manage_functions_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_manage_units_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_datasets_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_import_csv_file_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_export_csv_file_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_convert_to_unit_expression_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_convert_to_base_units_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_convert_to_best_unit_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_set_prefix_activate(GtkMenuItem*, gpointer user_data);
void on_menu_item_insert_matrix_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_insert_vector_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_enable_variables_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_enable_functions_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_enable_units_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_enable_unknown_variables_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_calculate_variables_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_enable_variable_units_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_allow_complex_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_allow_infinite_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_new_unknown_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_new_variable_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_new_matrix_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_new_vector_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_new_function_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_new_dataset_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_new_unit_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_rpn_mode_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_rpn_syntax_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_limit_implicit_multiplication_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_adaptive_parsing_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_ignore_whitespace_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_no_special_implicit_multiplication_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_fetch_exchange_rates_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_save_defs_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_save_mode_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_edit_prefs_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_degrees_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_radians_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_gradians_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_no_default_angle_unit_activate(GtkMenuItem *w, gpointer user_data);
void set_output_base_from_dialog(int base);
void output_base_updated_from_menu();
void on_menu_item_binary_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_octal_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_decimal_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_duodecimal_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_hexadecimal_activate(GtkMenuItem *w, gpointer user_data);
void on_number_base_spinbutton_base_value_changed(GtkSpinButton *w, gpointer user_data);
void on_menu_item_custom_base_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_roman_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_sexagesimal_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_time_format_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_set_base_activate(GtkMenuItem *w, gpointer user_data);
void on_set_base_radiobutton_output_binary_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_radiobutton_output_octal_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_radiobutton_output_decimal_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_radiobutton_output_duodecimal_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_radiobutton_output_hexadecimal_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_radiobutton_output_other_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_radiobutton_output_sexagesimal_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_radiobutton_output_time_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_radiobutton_output_roman_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_spinbutton_output_other_value_changed(GtkSpinButton *w, gpointer user_data);
void on_set_base_radiobutton_input_binary_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_radiobutton_input_octal_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_radiobutton_input_decimal_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_radiobutton_input_duodecimal_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_radiobutton_input_hexadecimal_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_radiobutton_input_other_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_radiobutton_input_roman_toggled(GtkToggleButton *w, gpointer user_data);
void on_set_base_spinbutton_input_other_value_changed(GtkSpinButton *w, gpointer user_data);
void convert_number_bases(const gchar *initial_expression, bool b_result = false);
void on_menu_item_convert_number_bases_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_periodic_table_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_assumptions_integer_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_assumptions_rational_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_assumptions_real_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_assumptions_complex_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_assumptions_number_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_assumptions_nonmatrix_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_assumptions_none_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_assumptions_nonzero_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_assumptions_positive_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_assumptions_nonnegative_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_assumptions_negative_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_assumptions_nonpositive_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_assumptions_unknown_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_assume_nonzero_denominators_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_abort_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_clear_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_display_normal_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_display_engineering_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_display_scientific_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_display_purely_scientific_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_display_non_scientific_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_display_no_prefixes_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_display_prefixes_for_selected_units_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_display_prefixes_for_currencies_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_display_prefixes_for_all_units_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_fraction_decimal_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_fraction_decimal_exact_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_fraction_combined_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_fraction_fraction_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_binary_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_roman_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_sexagesimal_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_time_format_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_octal_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_decimal_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_duodecimal_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_hexadecimal_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_custom_base_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_abbreviate_names_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_all_prefixes_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_denominator_prefixes_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_view_matrix_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_view_vector_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_display_normal_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_display_engineering_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_display_scientific_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_display_purely_scientific_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_display_non_scientific_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_display_no_prefixes_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_display_prefixes_for_selected_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_display_prefixes_for_currencies_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_display_prefixes_for_all_units_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_indicate_infinite_series_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_show_ending_zeroes_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_round_halfway_to_even_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_negative_exponents_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_sort_minus_last_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_fraction_decimal_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_fraction_decimal_exact_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_fraction_combined_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_fraction_fraction_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_interval_adaptive_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_interval_significant_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_interval_interval_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_interval_plusminus_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_interval_midpoint_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_all_prefixes_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_denominator_prefixes_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_place_units_separately_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_post_conversion_none_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_post_conversion_base_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_post_conversion_optimal_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_post_conversion_optimal_si_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_abbreviate_names_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_always_exact_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_try_exact_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_approximate_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_interval_arithmetic_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_save_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_save_image_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_copy_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_precision_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_decimals_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_plot_functions_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_factorize_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_simplify_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_expand_partial_fractions_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_set_unknowns_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_assume_nonzero_denominators_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_algebraic_mode_simplify_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_algebraic_mode_factorize_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_algebraic_mode_hybrid_activate(GtkMenuItem *w, gpointer user_data);
gboolean on_main_window_focus_in_event(GtkWidget *w, GdkEventFocus *e, gpointer user_data);

void on_button_registerup_clicked(GtkButton *button, gpointer user_data);
void on_button_registerdown_clicked(GtkButton *button, gpointer user_data);
void on_button_editregister_clicked(GtkButton *button, gpointer user_data);
void on_button_deleteregister_clicked(GtkButton *button, gpointer user_data);
void on_button_clearstack_clicked(GtkButton *button, gpointer user_data);
void on_stackview_selection_changed(GtkTreeSelection *treeselection, gpointer user_data);
void on_stackview_item_edited(GtkCellRendererText *renderer, gchar *path, gchar *new_text, gpointer user_data);
void on_stackview_item_editing_started(GtkCellRenderer *renderer, GtkCellEditable *editable, gchar *path, gpointer user_data);
void on_stackview_item_editing_canceled(GtkCellRenderer *renderer, gpointer user_data);

void on_historyview_selection_changed(GtkTreeSelection *select, gpointer);

void on_unit_edit_entry_name_changed(GtkEditable *editable, gpointer user_data);
void on_unit_edit_combobox_class_changed(GtkComboBox *om, gpointer user_data);
void on_unit_edit_checkbutton_mix_toggled(GtkToggleButton *w, gpointer);
void on_unit_edit_combo_system_changed(GtkComboBox *om, gpointer user_data);
void on_units_button_new_clicked(GtkButton *button, gpointer user_data);
void on_units_button_edit_clicked(GtkButton *button, gpointer user_data);
void on_units_button_insert_clicked(GtkButton *button, gpointer user_data);
void on_units_button_convert_to_clicked(GtkButton *button, gpointer user_data);
void on_units_button_delete_clicked(GtkButton *button, gpointer user_data);
void on_units_combobox_to_unit_changed(GtkComboBox *w, gpointer user_data);
void on_variables_button_new_clicked(GtkButton *button, gpointer user_data);
void on_variables_button_edit_clicked(GtkButton *button, gpointer user_data);
void on_variables_button_insert_clicked(GtkButton *button, gpointer user_data);
void on_variables_button_delete_clicked(GtkButton *button, gpointer user_data);
void on_variables_button_export_clicked(GtkButton *button, gpointer user_data);
void on_variables_button_close_clicked(GtkButton *button, gpointer user_data);
void on_functions_button_new_clicked(GtkButton *button, gpointer user_data);
void on_functions_button_edit_clicked(GtkButton *button, gpointer user_data);
void on_functions_button_insert_clicked(GtkButton *button, gpointer user_data);
void on_functions_button_apply_clicked(GtkButton *button, gpointer user_data);
void on_functions_button_delete_clicked(GtkButton *button, gpointer user_data);
void on_functions_button_close_clicked(GtkButton *button, gpointer user_data);
void on_datasets_button_close_clicked(GtkButton *button, gpointer user_data);
void on_function_edit_entry_name_changed(GtkEditable *editable, gpointer user_data);
void on_variable_edit_entry_name_changed(GtkEditable *editable, gpointer user_data);
void on_unknown_edit_checkbutton_custom_assumptions_toggled(GtkToggleButton *w, gpointer user_data);
void on_unknown_edit_combobox_type_changed(GtkComboBox *om, gpointer user_data);
void on_unknown_edit_combobox_sign_changed(GtkComboBox *om, gpointer user_data);

void on_function_changed();
void on_simple_function_changed();
void on_argument_changed();
void on_unit_changed();
void on_variable_changed();
void on_dataset_changed();
void on_dataobject_changed();
void on_dataproperty_changed();
void on_matrix_changed();
void on_unknown_changed();
void on_name_changed();

void on_dataset_edit_entry_name_changed(GtkEditable *editable, gpointer user_data);
void on_dataset_edit_button_new_property_clicked(GtkButton *button, gpointer user_data);
void on_dataset_edit_button_edit_property_clicked(GtkButton *button, gpointer user_data);
void on_dataset_edit_button_del_property_clicked(GtkButton *button, gpointer user_data);
void on_dataset_edit_button_names_clicked(GtkButton *button, gpointer user_data);

void on_datasets_button_newset_clicked(GtkButton *button, gpointer user_data);
void on_datasets_button_editset_clicked(GtkButton *button, gpointer user_data);
void on_datasets_button_delset_clicked(GtkButton *button, gpointer user_data);
void on_datasets_button_newobject_clicked(GtkButton *button, gpointer user_data);
void on_datasets_button_editobject_clicked(GtkButton *button, gpointer user_data);
void on_datasets_button_delobject_clicked(GtkButton *button, gpointer user_data);

void on_nbases_button_close_clicked(GtkButton *button, gpointer user_data);
void on_nbases_entry_decimal_changed(GtkEditable *editable, gpointer user_data);
void on_nbases_entry_binary_changed(GtkEditable *editable, gpointer user_data);
void on_nbases_entry_octal_changed(GtkEditable *editable, gpointer user_data);
void on_nbases_entry_hexadecimal_changed(GtkEditable *editable, gpointer user_data);
void on_nbases_entry_duo_changed(GtkEditable *editable, gpointer user_data);
void on_nbases_entry_roman_changed(GtkEditable *editable, gpointer user_data);
void on_nbases_entry_sexa_changed(GtkEditable *editable, gpointer user_data);

void on_percentage_button_clear_clicked(GtkWidget*, gpointer);

void on_menu_item_show_percentage_dialog_activate(GtkMenuItem *w, gpointer user_data);

void on_menu_item_show_calendarconversion_dialog_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_calendarconversion_activate(GtkMenuItem *w, gpointer user_data);
void on_popup_menu_item_to_utc_activate(GtkMenuItem *w, gpointer user_data);

void calendar_changed(GtkWidget*, gpointer);

void on_button_functions_clicked(GtkButton *button, gpointer user_data);
void on_button_variables_clicked(GtkButton *button, gpointer user_data);
void on_button_units_clicked(GtkButton *button, gpointer user_data);
void on_button_convert_clicked(GtkButton *button, gpointer user_data);

void on_menu_item_about_activate(GtkMenuItem *w, gpointer user_data);
void on_menu_item_help_activate(GtkMenuItem *w, gpointer user_data);

void on_precision_dialog_spinbutton_precision_value_changed(GtkSpinButton *w, gpointer user_data);
void on_precision_dialog_button_recalculate_clicked(GtkButton *w, gpointer user_data);
void on_decimals_dialog_spinbutton_max_value_changed(GtkSpinButton *w, gpointer user_data);
void on_decimals_dialog_spinbutton_min_value_changed(GtkSpinButton *w, gpointer user_data);
void on_decimals_dialog_checkbutton_max_toggled(GtkToggleButton *w, gpointer user_data);
void on_decimals_dialog_checkbutton_min_toggled(GtkToggleButton *w, gpointer user_data);

gboolean on_expressiontext_button_press_event(GtkWidget *w, GdkEventButton *event, gpointer user_data);

gboolean on_resultview_button_press_event(GtkWidget *w, GdkEventButton *event, gpointer user_data);
gboolean on_resultview_popup_menu(GtkWidget *w, gpointer user_data);

gboolean on_expressiontext_key_press_event(GtkWidget *w, GdkEventKey *event, gpointer user_data);

void on_expressionbuffer_cursor_position_notify();

gboolean on_resultview_draw(GtkWidget *w, cairo_t *cr, gpointer user_data);

gboolean on_tMatrixEdit_key_press_event(GtkWidget *w, GdkEventKey *event, gpointer user_data);
gboolean on_tMatrixEdit_button_press_event(GtkWidget *w, GdkEventButton *event, gpointer user_data);
gboolean on_tMatrixEdit_cursor_changed(GtkTreeView *w, gpointer user_data);

void on_matrix_edit_spinbutton_columns_value_changed(GtkSpinButton *w, gpointer user_data);
void on_matrix_edit_spinbutton_rows_value_changed(GtkSpinButton *w, gpointer user_data);

void on_matrix_edit_radiobutton_matrix_toggled(GtkToggleButton *w, gpointer user_data);
void on_matrix_edit_radiobutton_vector_toggled(GtkToggleButton *w, gpointer user_data);

gboolean on_tMatrix_key_press_event(GtkWidget *w, GdkEventKey *event, gpointer user_data);
gboolean on_tMatrix_button_press_event(GtkWidget *w, GdkEventButton *event, gpointer user_data);
gboolean on_tMatrix_cursor_changed(GtkTreeView *w, gpointer user_data);

void on_matrix_spinbutton_columns_value_changed(GtkSpinButton *w, gpointer user_data);
void on_matrix_spinbutton_rows_value_changed(GtkSpinButton *w, gpointer user_data);

void on_matrix_radiobutton_matrix_toggled(GtkToggleButton *w, gpointer user_data);
void on_matrix_radiobutton_vector_toggled(GtkToggleButton *w, gpointer user_data);

void on_csv_import_radiobutton_matrix_toggled(GtkToggleButton *w, gpointer user_data);
void on_csv_import_radiobutton_vectors_toggled(GtkToggleButton *w, gpointer user_data);
void on_csv_import_combobox_delimiter_changed(GtkComboBox *w, gpointer user_data);
void on_csv_import_button_file_clicked(GtkButton *button, gpointer user_data);

void on_csv_export_combobox_delimiter_changed(GtkComboBox *w, gpointer user_data);
void on_csv_export_button_file_clicked(GtkButton *button, gpointer user_data);
void on_csv_export_radiobutton_current_toggled(GtkToggleButton *w, gpointer user_data);
void on_csv_export_radiobutton_matrix_toggled(GtkToggleButton *w, gpointer user_data);

void on_type_label_date_clicked(GtkButton *w, gpointer user_data);
void on_type_label_file_clicked(GtkButton *w, gpointer user_data);

void on_functions_button_deactivate_clicked(GtkButton *w, gpointer user_data);
void on_variables_button_deactivate_clicked(GtkButton *w, gpointer user_data);
void on_units_button_deactivate_clicked(GtkButton *w, gpointer user_data);

void on_function_edit_button_subfunctions_clicked(GtkButton *w, gpointer user_data);
void on_function_edit_button_add_subfunction_clicked(GtkButton *w, gpointer user_data);
void on_function_edit_button_modify_subfunction_clicked(GtkButton *w, gpointer user_data);
void on_function_edit_button_remove_subfunction_clicked(GtkButton *w, gpointer user_data);
void on_function_edit_entry_subexpression_activate(GtkEntry *entry, gpointer user_data);
void on_function_edit_button_add_argument_clicked(GtkButton *w, gpointer user_data);
void on_function_edit_button_remove_argument_clicked(GtkButton *w, gpointer user_data);
void on_function_edit_button_modify_argument_clicked(GtkButton *w, gpointer user_data);
void on_function_edit_entry_argument_name_activate(GtkEntry *entry, gpointer user_data);
void on_function_edit_button_rules_clicked(GtkButton *w, gpointer user_data);
void on_argument_rules_checkbutton_enable_min_toggled(GtkToggleButton *w, gpointer user_data);
void on_argument_rules_checkbutton_enable_max_toggled(GtkToggleButton *w, gpointer user_data);
void on_argument_rules_checkbutton_enable_condition_toggled(GtkToggleButton *w, gpointer user_data);

void on_variable_edit_button_names_clicked(GtkButton *w, gpointer user_data);
void on_unknown_edit_button_names_clicked(GtkButton *w, gpointer user_data);
void on_matrix_edit_button_names_clicked(GtkButton *w, gpointer user_data);
void on_function_edit_button_names_clicked(GtkButton *w, gpointer user_data);
void on_unit_edit_button_names_clicked(GtkButton *w, gpointer user_data);

void on_names_edit_checkbutton_abbreviation_toggled(GtkToggleButton *w, gpointer user_data);
void on_names_edit_button_add_clicked(GtkButton *w, gpointer user_data);
void on_names_edit_button_modify_clicked(GtkButton *w, gpointer user_data);
void on_names_edit_button_remove_clicked(GtkButton *w, gpointer user_data);
void on_names_edit_entry_name_activate(GtkEntry *w, gpointer user_data);
void on_names_edit_entry_name_changed(GtkEditable *editable, gpointer user_data);

void on_plot_button_save_clicked(GtkButton *w, gpointer user_data);
void on_plot_button_add_clicked(GtkButton *w, gpointer user_data);
void on_plot_button_modify_clicked(GtkButton *w, gpointer user_data);
void on_plot_button_remove_clicked(GtkButton *w, gpointer user_data);
void on_plot_checkbutton_xlog_toggled(GtkToggleButton *w, gpointer user_data);
void on_plot_checkbutton_ylog_toggled(GtkToggleButton *w, gpointer user_data);
void on_plot_radiobutton_step_toggled(GtkToggleButton *w, gpointer user_data);
void on_plot_radiobutton_steps_toggled(GtkToggleButton *w, gpointer user_data);
void on_plot_entry_expression_activate(GtkEntry *entry, gpointer user_data);

void on_unit_dialog_button_apply_clicked(GtkButton *w, gpointer user_data);
void on_unit_dialog_button_ok_clicked(GtkButton *w, gpointer user_data);
void on_unit_dialog_entry_unit_activate(GtkEntry *entry, gpointer user_data);

void convert_from_convert_entry_unit();
void on_convert_button_convert_clicked(GtkButton *w, gpointer user_data);
void on_convert_entry_unit_activate(GtkEntry *entry, gpointer user_data);

void on_element_button_clicked(GtkButton *w, gpointer user_data);

void on_convert_entry_search_changed(GtkEntry *w, gpointer user_data);
void on_units_entry_search_changed(GtkEntry *w, gpointer user_data);
void on_units_convert_search_changed(GtkEntry *w, gpointer user_data);
void on_functions_entry_search_changed(GtkEntry *w, gpointer user_data);
void on_variables_entry_search_changed(GtkEntry *w, gpointer user_data);

void save_accels();

gboolean on_menu_key_press(GtkWidget *widget, GdkEventKey *event);

#ifdef __cplusplus
}
#endif

#endif

