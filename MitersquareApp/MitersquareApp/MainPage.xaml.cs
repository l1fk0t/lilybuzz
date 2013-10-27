using System;
using System.Windows;

using Microsoft.Phone.Controls;

namespace MitersquareApp
{
    using System.Device.Location;
    using System.Diagnostics;
    using System.Windows.Controls;
    using System.Windows.Media;
    using System.Windows.Shapes;
    using System.Windows.Threading;

    using Windows.Networking.Proximity;
    using Windows.Networking.Sockets;
    using Windows.Storage.Streams;

    using Microsoft.Phone.Maps.Controls;
    using Microsoft.Phone.Reactive;

    public partial class MainPage : PhoneApplicationPage
    {
        private GeoCoordinate[] coordinates;

        public MainPage()
        {
            InitializeComponent();

            // Sample code to localize the ApplicationBar
            //BuildLocalizedApplicationBar();

            this.PopulateData();
        }

        private async void PopulateData()
        {
            var coordinate = new GeoCoordinate(52.496760459223, 13.4545183181763);

            coordinates = new[] 
            { 
                coordinate, // current
             
                new GeoCoordinate(52.496969, 13.45683),
                new GeoCoordinate(52.496548, 13.458799),
                new GeoCoordinate(52.496143, 13.460585),
                new GeoCoordinate(52.495735, 13.461696),

                new GeoCoordinate(52.495147, 13.463423),
                new GeoCoordinate(52.492773, 13.462474), // treptow
                new GeoCoordinate(52.502168, 13.470027), // ostkreuz

                // secondLag
                new GeoCoordinate(52.495954, 13.464947),
                new GeoCoordinate(52.496803, 13.465569),
                new GeoCoordinate(52.496826, 13.466556),
                
                new GeoCoordinate(52.4975702990329, 13.4651566456314) // target
            };

            var venues = await FoursquareClient.GetVenuesByLocation(coordinate);

            foreach (var venue in venues)
            {
                this.list.Items.Add(venue);
            }

            this.ShowLocationOnMap(coordinate);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            this.AppToDevice(7);

            this.intro.Visibility = this.explore.Visibility = Visibility.Collapsed;
            this.map.Visibility = this.list.Visibility = Visibility.Visible;

            var observable = this.GetGpsStream();

            //var subscription = gpsStream.Subscribe(s => Deployment.Current.Dispatcher.BeginInvoke(() => test.Text = s));
        }

        private IObservable<GeoCoordinate> GetGpsStream()
        {
            return Observable.CreateWithDisposable<GeoCoordinate>(
                observer =>
                {
                    var i = 0;
                    var timer = new DispatcherTimer();
                    timer.Interval = TimeSpan.FromSeconds(1);
                    timer.Tick += (s, e) =>
                    {
                        if (i >= coordinates.Length)
                        {
                            timer.Stop();
                            return;
                        }
                        observer.OnNext(coordinates[i]);
                        i++;
                    };
                    timer.Start();

                    return Disposable.Empty;
                });
        }

        private async void AppToDevice(byte command)
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

                writer.WriteByte(command);
                writer.StoreAsync();
            }
        }

        private void List_OnSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var item = (VenueViewModel)this.list.SelectedItem;

            this.ShowLocationOnMap(item.Coordinate);
        }

        private void ShowLocationOnMap(GeoCoordinate coordinate)
        {
            var overlay = new MapOverlay
            {
                GeoCoordinate = coordinate,
                Content = new Ellipse() { Fill = new SolidColorBrush(Colors.Blue), Width = 30, Height = 30 }
            };
            var layer = new MapLayer();
            layer.Add(overlay);

            this.map.Layers.Clear();
            this.map.Layers.Add(layer);
            this.map.SetView(coordinate, 15);
        }
    }
}