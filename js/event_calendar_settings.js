/**
 * @file
 * Attaches the behaviors for the Jquery Event Calendar module.
 */

(function ($) {
    Drupal.behaviors.jquery_event_calendar = {
        attach: function (context, settings) {

            $('#jqueryEventCalendar').eventCalendar({
                eventsLimit: Drupal.settings.jquery_event_calendar.eventsLimit,
                monthNames: ["January", "February", "March", "April", "May", "June",
                    "July", "August", "September", "October", "November", "December"],
                dayNames: ['Sunday', 'Monday', 'Tuesday', 'Wednesday',
                    'Thursday', 'Friday', 'Saturday'],
                dayNamesShort: ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat'],
                txt_noEvents: Drupal.settings.jquery_event_calendar.txt_noEvents,
                txt_SpecificEvents_prev: Drupal.settings.jquery_event_calendar.txt_SpecificEvents_prev,
                txt_SpecificEvents_after: Drupal.settings.jquery_event_calendar.txt_SpecificEvents_after,
                txt_next: Drupal.settings.jquery_event_calendar.txt_next,
                txt_prev: Drupal.settings.jquery_event_calendar.txt_prev,
                txt_NextEvents: Drupal.settings.jquery_event_calendar.txt_NextEvents,
                txt_GoToEventUrl: Drupal.settings.jquery_event_calendar.txt_GoToEventUrl,
                showDayAsWeeks: Drupal.settings.jquery_event_calendar.showDayAsWeeks,
                startWeekOnMonday: Drupal.settings.jquery_event_calendar.startWeekOnMonday,
                showDayNameInCalendar: Drupal.settings.jquery_event_calendar.showDayNameInCalendar,
                showDescription: Drupal.settings.jquery_event_calendar.showDescription,
                onlyOneDescription: Drupal.settings.jquery_event_calendar.onlyOneDescription,
                openEventInNewWindow: Drupal.settings.jquery_event_calendar.openEventInNewWindow,
                eventsScrollable: Drupal.settings.jquery_event_calendar.eventsScrollable,
                jsonDateFormat: Drupal.settings.jquery_event_calendar.jsonDateFormat,
                dateFormat: Drupal.settings.jquery_event_calendar.dateFormat,
                moveSpeed: Drupal.settings.jquery_event_calendar.moveSpeed,
                moveOpacity: Drupal.settings.jquery_event_calendar.moveOpacity,
                jsonData: JSON.parse(Drupal.settings.jquery_event_calendar.jsonData),
                cacheJson: Drupal.settings.jquery_event_calendar.cacheJson
            });
        }
    };
}(jQuery));
