using System;
using System.Windows;

using Microsoft.Phone.Controls;

namespace MitersquareApp
{
    using System.Threading;
    using System.Windows.Threading;

    using Microsoft.Phone.Reactive;

    public partial class MainPage : PhoneApplicationPage
    {
        // Constructor
        public MainPage()
        {
            InitializeComponent();

            // Sample code to localize the ApplicationBar
            //BuildLocalizedApplicationBar();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var coords = new [] { "1", "2", "3", "4", "5" };

            var gpsStream = this.GetGpsStream(coords);

            var subscription = gpsStream.Subscribe(s => Deployment.Current.Dispatcher.BeginInvoke(() => test.Text = s));
        }

        private IObservable<string> GetGpsStream(string[] coords)
        {
            return Observable.CreateWithDisposable<string>(
                observer =>
                {
                    var i = 0;
                    var timer = new DispatcherTimer();
                    timer.Interval = TimeSpan.FromSeconds(1);
                    timer.Tick += (s, e) =>
                    {
                        if (i >= coords.Length)
                        {
                            timer.Stop();
                            return;
                        }
                        observer.OnNext(coords[i]);
                        i++;
                    };
                    timer.Start();

                    return Disposable.Empty;
                });
        }

        // Sample code for building a localized ApplicationBar
        //private void BuildLocalizedApplicationBar()
        //{
        //    // Set the page's ApplicationBar to a new instance of ApplicationBar.
        //    ApplicationBar = new ApplicationBar();

        //    // Create a new button and set the text value to the localized string from AppResources.
        //    ApplicationBarIconButton appBarButton = new ApplicationBarIconButton(new Uri("/Assets/AppBar/appbar.add.rest.png", UriKind.Relative));
        //    appBarButton.Text = AppResources.AppBarButtonText;
        //    ApplicationBar.Buttons.Add(appBarButton);

        //    // Create a new menu item with the localized string from AppResources.
        //    ApplicationBarMenuItem appBarMenuItem = new ApplicationBarMenuItem(AppResources.AppBarMenuItemText);
        //    ApplicationBar.MenuItems.Add(appBarMenuItem);
        //}
    }
}