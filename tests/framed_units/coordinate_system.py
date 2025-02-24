import plotly.graph_objects as go
import numpy as np

class CoordinateSystem:
    # define axis colors
    axs_color = {
        1: 'red',
        2: 'green',
        3: 'blue'
    }

    def __init__(self, pose, name):
        self.pose = self._check_input(pose)
        self.name = name
        self.traces = self._plot()

    @staticmethod
    def _check_input(to_check):
        # check if input is of type list and convert into np.ndarray
        if isinstance(to_check, list):
            to_check = np.asarray(to_check)

        # convert dtype into float
        to_check = to_check.astype(float)
        assert to_check.shape == (4, 4)
        return to_check

    def _plot(self):
        """
        function creates a coordinate system representation with plotly graph_objects.
        Each axis is stored in a separate trace.

        Returns:
            plotly.graph_objects traces
        """
        # define scaling factor for axis scaling (visibility on coordinate system)
        scaling_factor = 1  #self.points.max() / 10

        # create four points for displaying the coordinate system
        four_points = np.asarray([[0, 0, 0, 1], [1, 0, 0, 1], [0, 1, 0, 1], [0, 0, 1, 1]]) * scaling_factor

        # convert points into coordinate system
        converted_points = np.dot(self.pose, four_points.T)

        # create traces for input points and axes
        traces = [
            go.Scatter3d(
                x=converted_points[0, :],
                y=converted_points[1, :],
                z=converted_points[2, :],
                mode='markers',
                marker={'size': [10, 0, 0, 0], 'symbol': 'circle-open', 'color': 'black'},
                name='points-axis',
                showlegend=False
            )
        ]

        for axis, axis_name in enumerate(['x-axis', 'y-axis', 'z-axis'], start=1):
            traces.append(
                go.Scatter3d(
                    x=converted_points.T[[0, axis], 0],
                    y=converted_points.T[[0, axis], 1],
                    z=converted_points.T[[0, axis], 2],
                    mode='lines+markers',
                    marker={
                        'size': [0, 6],
                        'symbol': 'diamond',
                        'color': self.axs_color[axis],
                        'line': {'color': self.axs_color[axis]}
                    },
                    name=axis_name
                )
            )
        traces.append(
            go.Scatter3d(
                x=[converted_points[0, 0]],
                y=[converted_points[1, 0]],
                z=[converted_points[2, 0]],
                mode='text',
                text=[self.name],
                textposition='top center',
                name='origin-label'
            )
        )
        return traces