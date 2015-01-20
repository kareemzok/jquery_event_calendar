DESCRIPTION
-----------
This module integrates the wonderful jquery calendar plugin built by Jaime Fdez:
http://www.vissit.com/projects/eventCalendar/

Create and schedule different type of event in this calendar.
Check the diversity in content type.

REQUIREMENTS
------------
Drupal 7.x

This module requires the following contrib module :
 *  Date (https://www.drupal.org/project/date)
 *  libraries (https://www.drupal.org/project/libraries)


INSTALLATION
------------
 *  Install as you would normally install a contributed drupal module.For further information see:
    https://drupal.org/documentation/install/modules-themes/modules-7
 *  Download the Jquery event calendar library from https://github.com/jaime8111/jQueryEventCalendar
 *  Place the library in the appropriate directory E.G.
    sites/all/libraries/jquery-event-calendar
    sites/all/libraries/jquery-event-calendar/eventCalendar.css
    sites/all/libraries/jquery-event-calendar/eventCalendar_theme_responsive.css
    sites/all/libraries/jquery-event-calendar/jquery.eventCalendar.min.js
 *  You may need to wrap jquery.eventCalendar.min.js with (function ($) { ....... }(jQuery)); 
    if you got the following error : Cannot read property 'fn' of undefined


CONFIGURATION
-------------
 *  Jquery event calendar settings can be found at admin/config/user-interface/jquery-event-calendar.
 *  Settings are defined as groups.
 *  Once you have configured your settings, you will be able to see result on the calendar after placing the "Event calendar" block.
 *  Finally be sure you have selected the date field in settings and entered it in content.

