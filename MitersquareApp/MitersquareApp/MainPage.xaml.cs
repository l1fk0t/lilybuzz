using System;
using System.Windows;

using Microsoft.Phone.Controls;

namespace MitersquareApp
{
    using System.Device.Location;
    using System.Diagnostics;
    using System.Threading;
    using System.Windows.Threading;

    using Windows.Networking.Proximity;
    using Windows.Networking.Sockets;
    using Windows.Storage.Streams;

    using Microsoft.Phone.Maps.Controls;
    using Microsoft.Phone.Reactive;

    public partial class MainPage : PhoneApplicationPage
    {
        // Constructor
        public MainPage()
        {
            InitializeComponent();

            // Sample code to localize the ApplicationBar
            //BuildLocalizedApplicationBar();

            var coordinate = new GeoCoordinate(52.496760459223, 13.4545183181763);
            var response = FoursquareClient.GetVenuesByLocation(coordinate);

            this.map.SetView(coordinate, 14);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var coords = new [] { "1", "2", "3", "4", "5" };

            var gpsStream = this.GetGpsStream(coords);

            //var subscription = gpsStream.Subscribe(s => Deployment.Current.Dispatcher.BeginInvoke(() => test.Text = s));
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

        private async void AppToDevice()
        {
            // Configure PeerFinder to search for all paired devices.
            PeerFinder.AlternateIdentities["Bluetooth:Paired"] = "";
            var pairedDevices = await PeerFinder.FindAllPeersAsync();

            if (pairedDevices.Count == 0)
            {
                Debug.WriteLine("No paired devices were found.");
            }
            else
            {
                // Select a paired device. In this example, just pick the first one.
                PeerInformation selectedDevice = pairedDevices[0];
                // Attempt a connection
                StreamSocket socket = new StreamSocket();
                // Make sure ID_CAP_NETWORKING is enabled in your WMAppManifest.xml, or the next 
                // line will throw an Access Denied exception.
                // In this example, the second parameter of the call to ConnectAsync() is the RFCOMM port number, and can range 
                // in value from 1 to 30.
                await socket.ConnectAsync(selectedDevice.HostName, "1");

                var writer = new DataWriter(socket.OutputStream);

                writer.WriteInt32(7);
                writer.StoreAsync();
                writer.DetachStream();
            }
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