<?php

/**
 * @file
 * Generate configuration form and save settings.
 */

/**
 * Configuration form for slider options.
 */
function jquery_event_calendar_option_configuration_form($form, &$form_state) {

    $jquery_calandar_lib_path = variable_get('jquery_calandar_lib_path', 'sites/all/libraries/jquery-event-calendar');

    if (!file_exists($jquery_calandar_lib_path . '/jquery.eventCalendar.min.js')) {
        drupal_set_message(t('Can not find: ') . $jquery_calandar_lib_path . '/jquery.eventCalendar.min.js ' . t('You must upload the library to: ') . $jquery_calandar_lib_path, 'error');
    }

    $content_type_names = node_type_get_names();

    $form['general'] = array(
        '#type' => 'fieldset',
        '#title' => t('Jquery Calendar library'),
        '#collapsible' => true,
        '#collapsed' => false,
    );
    $form['general']['libpath']['#markup'] = t('Download Jquery Calendar library from: <a href="https://github.com/jaime8111/jQueryEventCalendar" target="_blank">Jquery Calendar Library download</a> then upload to. ' . $jquery_calandar_lib_path);


    $form['content'] = array(
        '#type' => 'fieldset',
        '#title' => t('Content type calendar configuration'),
        '#collapsible' => true,
        '#collapsed' => false,
    );
    if (!empty($content_type_names) && is_array($content_type_names)) {
        foreach ($content_type_names as $type => $name) {
            $form['content']["ct_" . $type] = array(
                '#type' => 'checkbox',
                '#title' => t($name),
                '#default_value' => variable_get('ct_' . $type, 0),
            );
            $form['content']['dropdown_date_fields_' . $type] = array(
                '#type' => 'select',
                '#prefix' => '<div id="dropdown-date-' . $type . '">',
                '#suffix' => '</div>',
                '#options' => _jquery_event_calendar_date_options($type),
                '#default_value' => variable_get('dropdown_date_fields_' . $type, 0),
                '#states' => array(
                    'visible' => array(
                        ':input[name=ct_' . $type . ']' => array('checked' => true),
                    ),
                ),
            );
        }
    }
    $form['config'] = array(
        '#type' => 'fieldset',
        '#title' => t('General Calendar configuration'),
        '#collapsible' => true,
        '#collapsed' => true,
    );
    $date_formats = array();
    $date_types = system_get_date_types();
    foreach ($date_types as $key => $value) {
        $date_formats[$value['type']] = t('@date_format format', array('@date_format' => $value['title'])) . ': ' . format_date(REQUEST_TIME, $value['type']);
    }

  
    $form['config']['jquery_event_calendar_dateformat'] = array(
        '#type' => 'textfield',
        '#title' => t('Date format'),
        '#description' => t('See the <a href="@url" target="_blank">Moment plugin</a> for date formats.', array('@url' => 'http://momentjs.com/docs/#/displaying/format/')),
        '#default_value' => variable_get('jquery_event_calendar_dateformat', 'dddd MM-D-YYYY'),
     
    );


    $form['config']['jquery_event_calendar_showDayAsWeeks'] = array(
        '#type' => 'select',
        '#title' => t('Show day as weeks'),
        '#options' => array(
            0 => t('False'),
            1 => t('True'),
        ),
        '#default_value' => variable_get('jquery_event_calendar_showDayAsWeeks', 1),
        '#description' => t('You can show all the days in a single line to make calendar widget smaller.'),
    );
    $form['config']['jquery_event_calendar_startWeekOnMonday'] = array(
        '#type' => 'select',
        '#title' => t('Start Week On Monday'),
        '#options' => array(
            0 => t('False'),
            1 => t('True'),
        ),
        '#default_value' => variable_get('jquery_event_calendar_startWeekOnMonday', 1),
        '#description' => t('Monday will be the day when the week starts.'),
    );
    $form['config']['jquery_event_calendar_showDayNameInCalendar'] = array(
        '#type' => 'select',
        '#title' => t('Show day name in calendar'),
        '#options' => array(
            0 => t('False'),
            1 => t('True'),
        ),
        '#default_value' => variable_get('jquery_event_calendar_showDayNameInCalendar', 1),
        '#description' => t('Hide the day names in the calendar view.'),
    );
    $form['config']['jquery_event_calendar_showDescription'] = array(
        '#type' => 'select',
        '#title' => t('Show description'),
        '#options' => array(
            0 => t('False'),
            1 => t('True'),
        ),
        '#default_value' => variable_get('jquery_event_calendar_showDescription', 0),
        '#description' => t('Show events description.'),
    );
    $form['config']['jquery_event_calendar_onlyOneDescription'] = array(
        '#type' => 'select',
        '#title' => t('Only one description'),
        '#options' => array(
            0 => t('False'),
            1 => t('True'),
        ),
        '#default_value' => variable_get('jquery_event_calendar_onlyOneDescription', 1),
        '#description' => t('By default, the plugin only shows the event that you select, but you can open all the descriptions in which you click on.'),
    );
    $form['config']['jquery_event_calendar_openEventInNewWindow'] = array(
        '#type' => 'select',
        '#title' => t('Open event in new window'),
        '#options' => array(
            0 => t('False'),
            1 => t('True'),
        ),
        '#default_value' => variable_get('jquery_event_calendar_openEventInNewWindow', 1),
        '#description' => t('Open event link in a new window.'),
    );
    $form['config']['jquery_event_calendar_eventsScrollable'] = array(
        '#type' => 'select',
        '#title' => t('Events scrollable'),
        '#options' => array(
            0 => t('False'),
            1 => t('True'),
        ),
        '#default_value' => variable_get('jquery_event_calendar_eventsScrollable', 0),
        '#description' => t('Add a Scroll panel for the events list to avoid panel resize on date changes.'),
    );
    $form['config']['jquery_event_calendar_cacheJson'] = array(
        '#type' => 'select',
        '#title' => t('Json Cash'),
        '#options' => array(
            0 => t('False'),
            1 => t('True'),
        ),
        '#default_value' => variable_get('jquery_event_calendar_cacheJson', 1),
        '#description' => t('If its true then the plugin only calls once to the json file, so it has to contain all events. After that call, the plugin will filter the results.'),
    );
    $form['config']['jquery_event_calendar_eventsLimit'] = array(
        '#type' => 'textfield',
        '#title' => t('Number of events showing'),
        '#maxlength' => 3,
        '#size' => 3,
        '#default_value' => variable_get('jquery_event_calendar_eventsLimit', '3'),
        '#description' => t('Limit number of events results only on load.'),
    );
    $form['config']['jquery_event_calendar_moveSpeed'] = array(
        '#type' => 'textfield',
        '#title' => t('Speed'),
        '#maxlength' => 10,
        '#size' => 10,
        '#default_value' => variable_get('jquery_event_calendar_moveSpeed', '500'),
        '#description' => t('Customize the speed of widget animation.'),
    );
    $form['config']['jquery_event_calendar_moveOpacity'] = array(
        '#type' => 'textfield',
        '#title' => t('Opacity'),
        '#maxlength' => 5,
        '#size' => 5,
        '#default_value' => variable_get('jquery_event_calendar_moveOpacity', '0.15'),
        '#description' => t('Opacity of widget animation.'),
    );

    $form['labels'] = array(
        '#type' => 'fieldset',
        '#title' => t('Text/label calendar configuration'),
        '#collapsible' => true,
        '#collapsed' => true,
    );


    $form['labels']['jquery_event_calendar_txt_noEvents'] = array(
        '#type' => 'textfield',
        '#title' => t('Label to display when no events showing'),
        '#maxlength' => 30,
        '#size' => 30,
        '#default_value' => variable_get('jquery_event_calendar_txt_noEvents', 'No events for this period'),
    );
    $form['labels']['jquery_event_calendar_txt_SpecificEvents_prev'] = array(
        '#type' => 'textfield',
        '#title' => t('Customize prefix of the event head date'),
        '#maxlength' => 30,
        '#size' => 30,
        '#default_value' => variable_get('jquery_event_calendar_txt_SpecificEvents_prev', ''),
    );
    $form['labels']['jquery_event_calendar_txt_SpecificEvents_after'] = array(
        '#type' => 'textfield',
        '#title' => t('Customize suffix of the event head date'),
        '#maxlength' => 30,
        '#size' => 30,
        '#default_value' => variable_get('jquery_event_calendar_txt_SpecificEvents_after', 'events:'),
    );
    $form['labels']['jquery_event_calendar_txt_next'] = array(
        '#type' => 'textfield',
        '#title' => t('Customize next arrow label'),
        '#maxlength' => 30,
        '#size' => 30,
        '#default_value' => variable_get('jquery_event_calendar_txt_next', 'Next'),
    );
    $form['labels']['jquery_event_calendar_txt_prev'] = array(
        '#type' => 'textfield',
        '#title' => t('Customize previous arrow label'),
        '#maxlength' => 30,
        '#size' => 30,
        '#default_value' => variable_get('jquery_event_calendar_txt_prev', 'Prev'),
    );

    $form['labels']['jquery_event_calendar_txt_NextEvents'] = array(
        '#type' => 'textfield',
        '#title' => t('Customize next events label'),
        '#maxlength' => 30,
        '#size' => 30,
        '#default_value' => variable_get('jquery_event_calendar_txt_NextEvents', 'Next events:'),
    );

    $form['labels']['jquery_event_calendar_txt_GoToEventUrl'] = array(
        '#type' => 'textfield',
        '#title' => t('Customize url event button'),
        '#maxlength' => 30,
        '#size' => 30,
        '#default_value' => variable_get('jquery_event_calendar_txt_GoToEventUrl', 'See the event'),
    );


    return system_settings_form($form);
}

function jquery_event_calendar_option_configuration_form_validate($form, &$form_state) {

    $bool = 0;
    $names = array_keys(node_type_get_names());
    foreach ($names as $name) {
        if ($form_state['values']['ct_' . $name] == 1) {
            $bool = 1;
        }
    }
    if ($bool == 0) {
        form_set_error('onthisdate_maxdisp', t('At least chose one content type.'));
    }
}

function _jquery_event_calendar_date_options($selected) {

    if ($selected != '') {
        $fields = field_info_fields();
        $options = array();
        $options[''] = t('No result found');
        if (!empty($fields) && is_array($fields)) {
            foreach ($fields as $name => $details) {
                if (isset($details['bundles']['node']))
                    $node = $details['bundles']['node'];
                if (isset($node) && !empty($node) && is_array($node)) {
                    foreach ($node as $type) {
                        if ($type == $selected) {
                            if (strpos($name, 'date') !== false) {
                                $options[''] = t('Chose a field');
                                $options[$name] = $name;
                            }
                        }
                    }
                }
            }
        }
    } else {
        $options = array();
    }
    return $options;
}
