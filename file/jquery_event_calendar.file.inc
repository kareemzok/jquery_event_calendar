<?php

/**
 * @file
 * Administrative or front  forms and functions for the jquery calendar module.
 */

/**
 * Eventcalendar_service_form - see hook_form - see api.drupal.org.
 * @author kareem zok 
 */
function jquery_event_calendar_services_form($form, &$form_state) {

    drupal_add_library('jquery_event_calendar', 'jquery-event-calendar');
    $form['calendar']['#prefix'] = '<div id="jqueryEventCalendar">';
    $form['calendar']['#suffix'] = '</div>';

  //$dateformat='MM-D-YYYY';
    drupal_add_js(
            array('jquery_event_calendar' =>
        array(
            'eventsLimit' => (int) check_plain(variable_get('jquery_event_calendar_eventsLimit', '3')),
            'showDayAsWeeks' => check_plain(variable_get('jquery_event_calendar_showDayAsWeeks', 1)) == 1 ? true : false,
            'startWeekOnMonday' => check_plain(variable_get('jquery_event_calendar_startWeekOnMonday', 1)) == 1 ? true : false,
            'showDayNameInCalendar' => check_plain(variable_get('jquery_event_calendar_showDayNameInCalendar', 1)) == 1 ? true : false,
            'showDescription' => check_plain(variable_get('jquery_event_calendar_showDescription', 0)) == 1 ? true : false,
            'onlyOneDescription' => check_plain(variable_get('jquery_event_calendar_onlyOneDescription', 1)) == 1 ? true : false,
            'openEventInNewWindow' => check_plain(variable_get('jquery_event_calendar_openEventInNewWindow', 1)) == 1 ? true : false,
            'eventsScrollable' => check_plain(variable_get('jquery_event_calendar_eventsScrollable', 0)) == 1 ? true : false,
            'cacheJson' => check_plain(variable_get('jquery_event_calendar_cacheJson', 1)) == 1 ? true : false,
            'moveSpeed' => (int) check_plain(variable_get('jquery_event_calendar_moveSpeed', '500')),
            'moveOpacity' => (int) check_plain(variable_get('jquery_event_calendar_moveOpacity', '0.15')),
            'txt_noEvents' => check_plain(variable_get('jquery_event_calendar_txt_noEvents', t('No events for this period'))),
            'txt_SpecificEvents_prev' => check_plain(variable_get('jquery_event_calendar_txt_SpecificEvents_prev', '')),
            'txt_SpecificEvents_after' => check_plain(variable_get('jquery_event_calendar_txt_SpecificEvents_after', t('events:'))),
            'txt_next' => check_plain(variable_get('jquery_event_calendar_txt_next', t('Next'))),
            'txt_prev' => check_plain(variable_get('jquery_event_calendar_txt_prev', t('Prev'))),
            'txt_NextEvents' => check_plain(variable_get('jquery_event_calendar_txt_NextEvents', t('Next events:'))),
            'txt_GoToEventUrl' => check_plain(variable_get('jquery_event_calendar_txt_GoToEventUrl', t('See the event'))),
            'jsonDateFormat' => "human",
            'dateFormat' => check_plain(variable_get('jquery_event_calendar_dateformat', 'dddd MM-D-YYYY')),
            'jsonData' => _jquery_event_calendar_getJson(),
        ),
            ), 'setting'
    );
    drupal_add_js(drupal_get_path('module', 'jquery_event_calendar') . '/js/event_calendar_settings.js', array('scope' => 'footer', 'type' => 'file'));

    return $form;
}

/**
 * Return json data of events.
 * @author kareem zok 
 */
function _jquery_event_calendar_getJson() {
    $content_type_names = node_type_get_names();

    foreach ($content_type_names as $type => $name) {
        if (variable_get('ct_' . $type) == 1) {
            $type_array[] = $type;
            $type_date_array[$type] = variable_get('dropdown_date_fields_' . $type);
        }
    };

    $arr = Array();
    if (!empty($type_array)) {
        $query = new EntityFieldQuery();
        $entities = $query->entityCondition('entity_type', 'node')
                ->propertyCondition('type', $type_array, 'in')
                ->propertyCondition('status', 1)
                ->execute();
        if (!empty($entities['node'])) {
            foreach ($entities['node'] as $value) {
                $eventdata = node_load($value->nid);

                $field = $type_date_array[$eventdata->type];

                $arr[] = array(
                    'date' => $eventdata->{$field}[LANGUAGE_NONE][0]["value"],
                    'title' => $eventdata->title,
                    'type' => '',
                    'description' => $eventdata->body[LANGUAGE_NONE][0]['value'],
                    'url' => drupal_get_path_alias('node/' . $value->nid)
                );
            }
        }
    }

    $jsondata = json_encode($arr);

    return $jsondata;
}

