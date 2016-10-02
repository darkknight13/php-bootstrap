<html>
<head>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
<script src="//cdnjs.cloudflare.com/ajax/libs/toastr.js/latest/toastr.min.js"></script>
<!-- Latest compiled and minified CSS -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>
<link rel="stylesheet" type="text/css" href="//cdnjs.cloudflare.com/ajax/libs/toastr.js/latest/toastr.min.css">
<title>Notification</title>
</head>
<body>
<?php 
include_once 'Extras/SanitizeFile.inc';
use Bootstrap\Panel as Bootstrap_Panel;
use Bootstrap\Tab as Bootstrap_Tab;
use Bootstrap\Button as Bootstrap_Button;
use Bootstrap\ProgressBar as Bootstrap_ProgressBar;
require_once 'Bootstrap\Panel.inc';
require_once 'Bootstrap\Tab.inc';
require_once 'Bootstrap\Button.inc';
require_once 'Bootstrap\ProgressBar.inc';

echo SanitizeFile::initiate('/www/htdocs/inc/rm backup | md pipe * & % * | cd pipe.php')->sanitizeFileName();
$html = Bootstrap_ProgressBar::initiate('ticket')->add_bar('60')->type('deafult')->showtext()->striped()->state('active')->generate();
$html .= Bootstrap_ProgressBar::initiate('ticket')->add_bar('60')->type('info')->showtext()->state('active')->generate();
$html .= Bootstrap_ProgressBar::initiate('ticket')->add_bar('60')->type('success')->showtext()->generate();
$html .= Bootstrap_ProgressBar::initiate('ticket')->add_bar('60')->type('warning')->showtext()->generate();
$html .= Bootstrap_ProgressBar::initiate('ticket')->add_bar('60')->type('danger')->showtext()->generate();
$html .= Bootstrap_ProgressBar::initiate('ticket')
        ->add_bar('10')->type('default')->showtext()->striped()->state('active')
        ->add_bar('15')->type('info')->showtext()->striped()->state('active')
        ->add_bar('20')->type('danger')->showtext()->striped()->state('active')
        ->add_bar('25')->type('success')->showtext()->striped()->state('active')
        ->add_bar('30')->type('warning')->showtext()->striped()->state('active')
        ->generate();
echo $html;
?>
</body>
<script>
toastr.options = {
		  "closeButton": true,
		  "debug": false,
		  "newestOnTop": false,
		  "progressBar": true,
		  "positionClass": "toast-top-right",
		  "preventDuplicates": false,
		  "onclick": null,
		  "showDuration": "300",
		  "hideDuration": "1000",
		  "timeOut": "5000",
		  "extendedTimeOut": "1000",
		  "showEasing": "swing",
		  "hideEasing": "linear",
		  "showMethod": "fadeIn",
		  "hideMethod": "fadeOut"
		}
</script>
</html>
<?php 
